import subprocess
import os
import sys


HELIUM_EXEC = "./helium.exe"
TEST_DIR = "tests"
TIMEOUT_SECONDS = 2


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


def compare_output(actual, expected, label, file_path):
    if expected is None:
        return True

    if actual != expected:
        print(f"{label} mismatch: {file_path}")
        print("----- expected -----")
        print(expected)
        print("----- got -----")
        print(actual)
        print("--------------------")
        return False

    return True


def run_test(file_path):
    result = run_program(file_path)

    if result["stderr"] == "TIMEOUT":
        print(f"TIMEOUT: {file_path}")
        return False

    expected_out = read_file(file_path.replace(".he", ".out"))
    expected_err = read_file(file_path.replace(".he", ".err"))

    error_test = is_error_test(file_path)

    passed = True


    if error_test:
        if result["stderr"] == "":
            print(f"Expected error but got none: {file_path}")
            return False
    else:
        if result["stderr"] != "":
            print(f"Unexpected error: {file_path}")
            print(result["stderr"])
            return False


    if not compare_output(result["stdout"], expected_out, "STDOUT", file_path):
        passed = False

    if not compare_output(result["stderr"], expected_err, "STDERR", file_path):
        passed = False

    return passed


def run_all_tests():
    total = 0
    passed = 0

    for root, _, files in os.walk(TEST_DIR):
        for file in files:
            if file.endswith(".he"):
                total += 1
                path = os.path.join(root, file)

                if run_test(path):
                    passed += 1

    print("\n======================")
    print(f"Passed {passed}/{total} tests")

    if passed != total:
        sys.exit(1)


if __name__ == "__main__":
    run_all_tests()
