import os
import subprocess
import sys
import time
import statistics
import math
import platform
from datetime import datetime

BASE_DIR = "benchmarks"
RUNS = 10
WARMUP_RUNS = 2


# ------------------------
# Utility helpers
# ------------------------

def get_output(cmd):
    try:
        result = subprocess.run(cmd, capture_output=True, text=True, shell=True)
        return result.stdout.strip() or result.stderr.strip()
    except:
        return ""


# ------------------------
# Language naming
# ------------------------

def get_language_name(filename):
    ext = os.path.splitext(filename)[1]

    if ext == ".py":
        out = get_output("python --version")
        version = out.replace("Python ", "")
        return f"Python ({version})"

    elif ext == ".js":
        out = get_output("node --version")
        return f"JavaScript (Node {out})"

    elif ext == ".rb":
        out = get_output("ruby --version")
        return f"Ruby ({out.split()[1]})"

    elif ext == ".pl":
        out = get_output("perl --version")
        first_line = out.split("\n")[0]

        import re
        match = re.search(r"\(v([\d\.]+)\)", first_line)

        if match:
            version = match.group(1)
            return f"Perl ({version})"

        return "Perl"

    elif ext == ".c":
        return "C (GCC 6.3.0, -O2)"

    elif ext == ".he":
        return "Helium"

    return filename


def make_clickable_name(filename, folder=None):
    lang = get_language_name(filename)

    if folder:
        path = f"./{folder}/{filename}"
    else:
        path = f"./{filename}"

    return f'<a href="{path}" target="_blank">{lang}</a>'


# ------------------------
# Running programs
# ------------------------

def run_command(cmd):
    try:
        start = time.perf_counter()

        subprocess.run(
            cmd,
            stdout=subprocess.DEVNULL,
            stderr=subprocess.DEVNULL,
            shell=True
        )

        end = time.perf_counter()
        return end - start

    except Exception as e:
        print(f"\nError running {cmd}: {e}")
        return None


def get_command(filepath):
    ext = os.path.splitext(filepath)[1]

    if ext == ".py":
        return f'python "{filepath}"'

    elif ext == ".c":
        exe_path = filepath.replace(".c", ".exe")
        compile_cmd = f'gcc "{filepath}" -O2 -o "{exe_path}"'
        subprocess.run(compile_cmd, shell=True)
        return f'"{exe_path}"'

    elif ext == ".he":
        return f'helium "{filepath}"'

    elif ext == ".pl":
        return f'perl "{filepath}"'

    elif ext == ".js":
        return f'node "{filepath}"'

    elif ext == ".rb":
        return f'ruby "{filepath}"'

    return None


# ------------------------
# Benchmark execution
# ------------------------

def benchmark_file(filepath):
    cmd = get_command(filepath)
    if not cmd:
        return None

    filename = os.path.basename(filepath)
    times = []

    print(f"\nRunning {filename}")

    # Warmup runs help reduce startup noise and caching effects
    for _ in range(WARMUP_RUNS):
        subprocess.run(cmd, stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL, shell=True)

    # Actual measured runs
    for i in range(RUNS):
        print(f"\r   Progress: [{i+1}/{RUNS}]", end="", flush=True)

        t = run_command(cmd)
        if t is not None:
            times.append(t)

    print()

    if not times:
        return None

    median = statistics.median(times)
    std = statistics.stdev(times) if len(times) > 1 else 0

    return {
        "file": filename,
        "times": times,
        "median": median,
        "std": std
    }


# ------------------------
# Table formatting
# ------------------------

def format_table_vs_helium(results):
    lines = []
    lines.append("| Program | Median Time | Std Dev | vs Helium |")
    lines.append("|--------|------------------|---------|-------------|")

    helium = next((r for r in results if r["file"].endswith(".he")), None)
    if not helium:
        return "Helium result not found.\n"

    h_time = helium["median"]

    for r in results:
        ratio = r["median"] / h_time
        name = make_clickable_name(r["file"])

        if ratio > 1:
            comp = f"{ratio:.2f}x slower"
        elif ratio < 1:
            comp = f"{(1/ratio):.2f}x faster"
        else:
            comp = "1.00x (baseline)"

        lines.append(
            f"| {name} | {r['median']:.6f} | {r['std']:.6f} | {comp} |"
        )

    return "\n".join(lines)


def format_table_global_vs_helium(results, folder):
    lines = []
    lines.append("| Program | Median Time | Std Dev | vs Helium |")
    lines.append("|--------|------------------|---------|-------------|")

    helium = next((r for r in results if r["file"].endswith(".he")), None)
    if not helium:
        return "Helium result not found.\n"

    h_time = helium["median"]

    for r in results:
        ratio = r["median"] / h_time
        name = make_clickable_name(r["file"], folder)

        if ratio > 1:
            comp = f"{ratio:.2f}x slower"
        elif ratio < 1:
            comp = f"{(1/ratio):.2f}x faster"
        else:
            comp = "1.00x (baseline)"

        lines.append(
            f"| {name} | {r['median']:.6f} | {r['std']:.6f} | {comp} |"
        )

    return "\n".join(lines)


def format_helium_comparison(results):
    helium = next((r for r in results if r["file"].endswith(".he")), None)
    if not helium:
        return "Helium result not found.\n"

    lines = []
    h_time = helium["median"]

    for r in results:
        if r == helium:
            continue

        ratio = r["median"] / h_time
        lang = get_language_name(r["file"])

        if ratio > 1:
            lines.append(f"- {lang} is {ratio:.2f}x slower than Helium")
        else:
            lines.append(f"- {lang} is {(1/ratio):.2f}x faster than Helium")

    return "\n".join(lines)


# ------------------------
# System info + methodology
# ------------------------

def get_system_info():
    lines = []

    lines.append("## Benchmark Methodology\n")
    lines.append("- Each benchmark is executed multiple times to reduce noise.")
    lines.append(f"- Warmup runs: {WARMUP_RUNS}")
    lines.append(f"- Measured runs: {RUNS}")
    lines.append("- Median execution time is used for comparison.")
    lines.append("- Output is suppressed to avoid affecting timings.")
    lines.append("- Each program runs as a separate process.")
    lines.append("- C programs are compiled with `-O2` optimization.\n")

    lines.append("## System Information\n")
    lines.append(f"- OS: Windows 11")

    cpu = "Unknown CPU"
    try:
        cpu_out = get_output("wmic cpu get name")
        cpu_lines = [line.strip() for line in cpu_out.splitlines() if line.strip()]

        if len(cpu_lines) >= 2:
            cpu = cpu_lines[1]
    except:
        pass

    lines.append(f"- CPU: {cpu}")

    ram = "Unknown"
    try:
        ram_out = get_output("wmic computersystem get TotalPhysicalMemory")
        ram_lines = [line.strip() for line in ram_out.splitlines() if line.strip()]

        if len(ram_lines) >= 2:
            total_bytes = int(ram_lines[1])
            total_gb = total_bytes / (1024 ** 3)
            ram = f"{total_gb:.2f}GB"
    except:
        pass

    lines.append(f"- RAM: {ram}")

    lines.append(f"- Time: {datetime.now().strftime('%Y-%m-%d %H:%M:%S')}\n")

    return "\n".join(lines)


# ------------------------
# Overall stats
# ------------------------

def geometric_mean(values):
    return math.exp(sum(math.log(v) for v in values) / len(values))


def compute_overall_vs_helium(all_results):
    lang_ratios = {}

    for results in all_results.values():
        if not results:
            continue

        helium = next((r for r in results if r["file"].endswith(".he")), None)
        if not helium:
            continue

        h_time = helium["median"]

        for r in results:
            lang = get_language_name(r["file"])
            ratio = r["median"] / h_time

            lang_ratios.setdefault(lang, []).append(ratio)

    avg_ratios = {
        lang: geometric_mean(vals)
        for lang, vals in lang_ratios.items()
    }

    return sorted(avg_ratios.items(), key=lambda x: x[1])


def format_overall_vs_helium(sorted_langs):
    lines = []
    lines.append("## Overall Performance (Helium Baseline)\n")
    lines.append("| Language | vs Helium |")
    lines.append("|----------|-----------|")

    for lang, ratio in sorted_langs:
        if ratio > 1:
            lines.append(f"| {lang} | {ratio:.2f}x slower |")
        elif ratio < 1:
            lines.append(f"| {lang} | {(1/ratio):.2f}x faster |")
        else:
            lines.append(f"| {lang} | 1.00x (baseline) |")

    return "\n".join(lines)


# ------------------------
# Folder processing
# ------------------------

def process_folder(folder_path):
    results = []

    print(f"\nBenchmarking: {folder_path}")

    for file in os.listdir(folder_path):
        filepath = os.path.join(folder_path, file)

        if os.path.isfile(filepath):
            res = benchmark_file(filepath)
            if res:
                results.append(res)

    if not results:
        return []

    results.sort(key=lambda x: x["median"])

    output_path = os.path.join(folder_path, "results.md")

    with open(output_path, "w") as f:
        name = os.path.basename(folder_path)

        f.write(f"# Benchmark Results ({name})\n\n")
        f.write("## Summary\n\n")
        f.write(format_table_vs_helium(results))
        f.write("\n\n---\n\n")

        f.write("## Helium Comparison\n")
        f.write(format_helium_comparison(results))
        f.write("\n\n")

    print(f"Written: {output_path}")
    return results


# ------------------------
# Global report
# ------------------------

def write_global_results(all_results):
    output_path = os.path.join(BASE_DIR, "results.md")

    with open(output_path, "w") as f:
        f.write("# Global Benchmark Results\n\n")

        # Add methodology + system info
        f.write(get_system_info())
        f.write("\n---\n\n")

        overall = compute_overall_vs_helium(all_results)
        f.write(format_overall_vs_helium(overall))
        f.write("\n\n---\n\n")

        for folder, results in all_results.items():
            if not results:
                continue

            f.write(f"## {folder}\n\n")
            f.write(format_table_global_vs_helium(results, folder))
            f.write("\n\n")

            f.write("### Helium comparison:\n")
            f.write(format_helium_comparison(results))
            f.write("\n\n")

    print(f"\nGlobal results written: {output_path}")


# ------------------------
# Entry point
# ------------------------

def run_all():
    all_results = {}

    for subfolder in os.listdir(BASE_DIR):
        folder_path = os.path.join(BASE_DIR, subfolder)

        if os.path.isdir(folder_path):
            results = process_folder(folder_path)
            all_results[subfolder] = results

    write_global_results(all_results)

def run_single(folder_path):
    results = process_folder(folder_path)

    folder_name = os.path.basename(os.path.normpath(folder_path))
    write_global_results({folder_name: results})

def main(folder_path=None):
    if folder_path is None:
        run_all()
    else:
        run_single(folder_path)

if __name__ == "__main__":
    main(sys.argv[1] if len(sys.argv) > 1 else None)
