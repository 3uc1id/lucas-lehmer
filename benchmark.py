from subprocess import run
from time import perf_counter_ns
import statistics

TRIALS = 10


def main():
    exponents = [
        89, 107, 127, 521, 607, 1279,
        2203, 2281, 3217, 4253, 4423,
        9689, 9941, 11213, 19937, 21701,
        23209, 44497, 86243, 110503, 132049,
        216091, 756839, 859433
    ]

    table = [['Exponent', 'Min (ns)', 'Median (ns)', 'Max (ns)', 'Stdev (ns)']]
    for e in map(str, exponents):
        trials = []
        for _ in range(TRIALS):
            start = perf_counter_ns()
            result = run(['./lucas-lehmer', e], capture_output=True)
            end = perf_counter_ns()
            if result.returncode == 1 or result.stdout != b'PRIME':
                print('Erroneous result for ', e)
                continue
            trials.append(end - start)
        table.append([e,
                      min(trials),
                      statistics.median(trials),
                      max(trials),
                      statistics.stdev(trials)])

    column_widths = [*map(lambda col: max(map(len, col)) + 2, zip(*table))]
    
