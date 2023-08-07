import os
import csv
import sys

import pprint

BASE_DIR = os.path.dirname(os.path.abspath(__file__))


def keys():
    key_list = [
        'Roll No.',
        'Errors',
        'Success',
        'Failure',
        'Binary Found',
        'Conflicts Found',
    ]

    for testcase in sorted(os.listdir(BASE_DIR + '/tests')):
        key_list.append(testcase[:-2])

    return key_list


def evaluate(roll_no):
    DUMP_DIR = os.path.join(BASE_DIR, 'dump', str(roll_no))
    data_per_group = {
        'Roll No.': roll_no,
        'Errors': 'None',
        'Success': 0,
        'Failure': 0,
        'Binary Found': '',
        'Conflicts Found': '',
    }

    # Errors
    if os.path.exists(DUMP_DIR + '/error.dump'):
        with open(DUMP_DIR + '/error.dump') as error_file:
            data_per_group['Errors'] = error_file.readlines()[0][:-1]
        print('Compilation check: Fail')
        print('Errors: ', data_per_group['Errors'])
        return data_per_group
    else:
        data_per_group['Errors'] = 'None'
        print('Compilation check: Pass')

    # Binary
    with open(DUMP_DIR + '/binaries.dump') as binaries_file:
        if len(binaries_file.readlines()) > 0:
            data_per_group['Binary Found'] = 1
            print('Pre-compiled binary check: Fail')
        else:
            data_per_group['Binary Found'] = 0
            print('Pre-compiled binary check: Pass')

    # g++ version and Conflicts
    with open(DUMP_DIR + '/make_all.dump') as make_all_file:
        content = make_all_file.read()
        if 'conflicts' in content:
            data_per_group['Conflicts Found'] = 1
            print('Parser conflict check: Fail')
        else:
            data_per_group['Conflicts Found'] = 0
            print('Parser conflict check: Pass')

    # Tests
    success = 0
    failure = 0
    with open(DUMP_DIR + '/diff.dump') as diff_dump:
        for line in diff_dump:
            if line.split()[1] == 'total':
                continue
            testcase = line.split()[1].split('/')[3][:-5]
            if int(line.split()[0]) > 0:
                data_per_group[testcase] = 0
                failure += 1
            else:
                data_per_group[testcase] = 1
                success += 1
    data_per_group['Success'] = success
    data_per_group['Failure'] = failure

    if failure == 0:
        print('All testcases passed')

    return data_per_group


def dump_csv(roll_no):
    results = []
    results.append(evaluate(roll_no))

    with open(BASE_DIR + '/final.csv', 'w') as outfile:
        writer = csv.DictWriter(outfile, keys())
        writer.writeheader()
        writer.writerows(results)


if __name__ == '__main__':
    try:
        roll_no = int(sys.argv[1])
    except:
        print("Usage: python eval.py <roll_no>")
        exit(1)

    dump_csv(roll_no)
