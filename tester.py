import subprocess
import os
import sys
import difflib


HELIUM_EXEC = "./helium.exe"
TEST_DIR = "tests"
TIMEOUT_SECONDS = 2


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


def run_test(file_path):
    result = run_program(file_path)

    expected_out = read_file(file_path.replace(".he", ".out"))
    expected_err = read_file(file_path.replace(".he", ".err"))

    error_test = is_error_test(file_path)

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

    
    if errors:
        print(color(f"\nFAIL: {file_path}", Colors.RED))

        for err in errors:
            if isinstance(err, str):
                print(color(err, Colors.RED))
            else:
                label, expected, actual = err
                print(color(f"\n{label} mismatch:", Colors.RED))
                print_diff(expected, actual)

        return False

    return True


def run_all_tests():
    total = 0
    passed = 0

    print(color("\n=== Helium Test Runner ===\n", Colors.BOLD))

    for root, _, files in os.walk(TEST_DIR):
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


if __name__ == "__main__":
    run_all_tests()