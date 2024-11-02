from subprocess import run
from time import perf_counter_ns
import statistics

TRIALS = 100
TIME_FMT = '{:.3f}'


def main():
    exponents = [
        89, 107, 127, 521, 607, 1279,
        2203, 2281, 3217, 4253, 4423,
        9689, 9941, 11213, 19937, 21701,
        23209, 44497, 86243, 110503, 132049,
    ]
    #    216091, 756839, 859433
    #]

    table = [['Exponent', 'Min (µs)', 'Median (µs)', 'Max (µs)', 'Stdev (µs)']]
    for e in map(str, exponents):
        trials = []
        for _ in range(TRIALS):
            start = perf_counter_ns()
            result = run(['./lucas-lehmer', e], capture_output=True)
            end = perf_counter_ns()
            if result.returncode == 1 or result.stdout != b'PRIME\n':
                print('Erroneous result for ', e)
                continue
            trials.append((end - start)/1000)
        table.append([e,
                      TIME_FMT.format(min(trials)),
                      TIME_FMT.format(statistics.median(trials)),
                      TIME_FMT.format(max(trials)),
                      TIME_FMT.format(statistics.stdev(trials))])

    columns = [*zip(*table)]
    column_widths = [max(map(len, col))+2 for col in columns]
    row_sep = '+' + '+'.join('-'*w for w in column_widths) + '+'
    adjusted_cols = [[entry.rjust(w) for entry in col] for w, col in zip(column_widths, columns)]
    rows = ['|'.join(row) for row in zip(*adjusted_cols)]
    
    print(row_sep)
    for row in rows:
        print('|', row, '|', sep='')
        print(row_sep)
    

if __name__ == '__main__':
    main()
