import subprocess
import os
import sys
import difflib
import time


HELIUM_EXEC = "./helium.exe"
TEST_DIR = "tests"
TIMEOUT_SECONDS = 2
VERBOSE = False
STATS = False

TOTAL_TIME = 0

SLOWEST_TIME = 0
SLOWEST_TEST = ""

# ANSI colors
class Colors:
    GREEN = "\033[92m"
    RED = "\033[91m"
    YELLOW = "\033[93m"
    CYAN = "\033[96m"
    BOLD = "\033[1m"
    RESET = "\033[0m"


def color(text, c):
    return f"{c}{text}{Colors.RESET}"


def run_program(file_path):
    try:
        result = subprocess.run(
            [HELIUM_EXEC, file_path],
            capture_output=True,
            text=True,
            timeout=TIMEOUT_SECONDS
        )
    except subprocess.TimeoutExpired:
        return {
            "stdout": "",
            "stderr": "TIMEOUT",
            "exit_code": -1
        }

    return {
        "stdout": result.stdout.strip(),
        "stderr": result.stderr.strip(),
        "exit_code": result.returncode
    }


def read_file(path):
    if not os.path.exists(path):
        return None
    with open(path, "r") as f:
        return f.read().strip()


def is_error_test(file_path):
    return os.path.basename(file_path).startswith("err_")


def print_diff(expected, actual):
    expected_lines = (expected or "").splitlines()
    actual_lines = (actual or "").splitlines()

    diff = difflib.ndiff(expected_lines, actual_lines)

    print(color("----- diff -----", Colors.YELLOW))
    for line in diff:
        if line.startswith("- "):
            print(color(line, Colors.GREEN))     # expected but missing
        elif line.startswith("+ "):
            print(color(line, Colors.RED))    # extra in actual
        elif line.startswith("? "):
            print(color(line, Colors.YELLOW))  # pointer to exact change
        else:
            print(line)  # unchanged
    print(color("----------------", Colors.YELLOW))


def run_test(file_path: str):
    global TOTAL_TIME, SLOWEST_TIME, SLOWEST_TEST

    start_time = time.perf_counter()
    
    result = run_program(file_path)

    elapsed = time.perf_counter() - start_time



    base, _ = os.path.splitext(file_path)

    expected_out = read_file(base + ".out")
    expected_err = read_file(base + ".err")

    

    error_test = is_error_test(file_path)

    if expected_out is None and expected_err is None:
        if error_test:
            print(f"Missing validation file: {color(file_path.removesuffix('.he') + '.err', Colors.RED)}")
        else:    
            print(f"Missing validation file: {color(file_path.removesuffix('.he') + '.out', Colors.RED)}")
        sys.exit(1)

    errors = []

    # Timeout
    if result["stderr"] == "TIMEOUT":
        errors.append("TIMEOUT")

    # Error expectation
    if error_test:
        if result["stderr"] == "":
            errors.append("Expected error but got none")
    else:
        if result["stderr"] != "":
            errors.append(f"Unexpected error:\n{result['stderr']}")

    # STDOUT check
    if expected_out is not None and result["stdout"] != expected_out:
        errors.append(("STDOUT", expected_out, result["stdout"]))

    # STDERR check
    if expected_err is not None and result["stderr"] != expected_err:
        errors.append(("STDERR", expected_err, result["stderr"]))

    # check crash
    if result["exit_code"] < 0:
        errors.append("Process crashed")

    
    if errors:
        print(color(f"\nFAIL: {file_path} ({formatTimeElapsed(elapsed)}{color(')', Colors.RED)}", Colors.RED))

        for err in errors:
            if isinstance(err, str):
                print(color(err, Colors.RED))
            else:
                label, expected, actual = err
                print(color(f"\n{label} mismatch:", Colors.RED))
                print_diff(expected, actual)

        return False

    if VERBOSE:
        print(color(f"PASS: {file_path}", Colors.GREEN))
    if STATS:
        label = f"Time taken ({file_path}):"
        padded = label.ljust(70)

        colored_label = padded.replace(
            file_path,
            color(file_path, Colors.YELLOW)
        )

        printTimeElapsed(colored_label, elapsed)

    if elapsed > SLOWEST_TIME:
        SLOWEST_TIME = elapsed
        SLOWEST_TEST = file_path

    TOTAL_TIME += elapsed
    return True

def run_file(file_path: str):
    if not os.path.isfile(file_path):
        print(color(f"File not found: {file_path}", Colors.RED))
        sys.exit(1)
    print(color("\n=== Helium Test Runner ===\n", Colors.BOLD))
    print(f"> running tests for {color(file_path, Colors.CYAN)}")
    result = run_test(file_path)
    print(color("\n======================", Colors.BOLD))
    if result:
        print(f"Test {color('passed', Colors.GREEN)}")
    else:
        print(f"Test {color('failed', Colors.RED)}")



def run_test_folder(folder_path: str):
    if not os.path.isdir(folder_path):
        print(color(f"Test folder not found: {folder_path}", Colors.RED))
        sys.exit(1)
    total = 0
    passed = 0

    print(color("\n=== Helium Test Runner ===\n", Colors.BOLD))
    print(f"> running tests for {color(folder_path, Colors.CYAN)}")
    for root, _, files in os.walk(folder_path):
        for file in files:
            if file.endswith(".he"):
                total += 1
                path = os.path.join(root, file)

                if run_test(path):
                    passed += 1

    percent = (passed / total * 100) if total else 0

    print(color("\n======================", Colors.BOLD))
    print(f"Passed: {color(str(passed), Colors.GREEN)}/{total}")
    print(f"Success Rate: {color(f'{percent:.2f}%', Colors.CYAN)}")

    if passed != total:
        sys.exit(1)

def run_all_tests():
    run_test_folder(TEST_DIR)


def run_test_from_path(arg: str):
    match arg:
        case "all":
            run_all_tests()
        case _:
            if arg.endswith(".he"):
                run_file(arg)
            else:
                run_test_folder(arg)

def run_test_with_args(args: list[str]):
    global VERBOSE, STATS

    path = TEST_DIR

    for arg in args:
        match arg:
            case "-v" | "--verbose":
                VERBOSE = True
            case "-s" | "--stats":
                STATS = True
            case _ if arg.startswith("-"):
                print(f"Invalid argument passed {color(arg, Colors.RED)}")
                print("usage: python tester.py [path] [-v] [-s]")
                sys.exit(1)
            case _:
                path = arg

    run_test_from_path(path)


def formatTimeElapsed(elapsed) -> str:
    if elapsed < 0.001:
        return (f"{color(f'{elapsed * 1_000_000:.2f} µs', Colors.CYAN)}")
    elif elapsed < 1:
        return (f"{color(f'{elapsed * 1000:.2f} ms', Colors.CYAN)}")
    else:
        return (f"{color(f'{elapsed:.3f} s', Colors.CYAN)}")

def printTimeElapsed(text: str, elapsed: float):
    print(f"{text} {formatTimeElapsed(elapsed)}")

if __name__ == "__main__":
    if not os.path.isfile(HELIUM_EXEC):
        print(color(f"Helium executable not found: {HELIUM_EXEC}", Colors.RED))
        sys.exit(1)
    
    run_test_with_args(sys.argv[1::])

    printTimeElapsed("Total time taken:", TOTAL_TIME)
    print(f"Slowest test: {color(SLOWEST_TEST, Colors.YELLOW)}")
    printTimeElapsed("Time:", SLOWEST_TIME)