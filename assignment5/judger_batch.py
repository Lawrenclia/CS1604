import time
import random
import os
import subprocess
import argparse
import sys
import shutil
import tempfile

exec_name = {
    '1_matrix': [['main.cpp', 'matrix.cpp'], 'matrix'],
    '2_gitArray': [['main.cpp', 'gitArray.cpp'], 'gitArray']
}

# exec_name: {'task_name': ['main.cpp', 'executable']}

# uniform test point names for each task
input_name = ['1.in', '2.in', '3.in', '4.in', '5.in']
output_name = ['1.out', '2.out', '3.out', '4.out', '5.out']


def init_args():
    parser = argparse.ArgumentParser('Judger For Homework 5')
    parser.add_argument(
        '-T', '--task', choices=list(exec_name.keys()),
        help='the task to judge'
    )
    parser.add_argument(
        '-I', '--input_dir', required=False,
        help='the path of input data file'
    )
    parser.add_argument(
        '-O', '--standard_dir', required=False,
        help='the path of standard output file'
    )
    parser.add_argument(
        '-S', '--source_dir', required=False,
        help='the folder containing the source code'
    )
    parser.add_argument(
        '--timeout', default=20, type=float,
        help='the timeout for judging (in seconds), default is 20'
    )

    args = parser.parse_args()

    # set the directories of input, output and source code
    if args.input_dir is None:
        args.input_dir = os.path.join('data', args.task)
    if args.standard_dir is None:
        args.standard_dir = os.path.join('data', args.task)
    if args.source_dir is None:
        args.source_dir = args.task

    return args


def get_random_filename():
    lst = []
    for x in range(10):
        lst.append(chr(ord('A') + random.randint(0, 25)))
    temp_path = ''.join(lst)
    return temp_path


def standard_judger(answer, std, max_score=10):
    # 忽略行末空格和文末空行
    with open(std) as Fin:
        c_std = Fin.read()
        c_std = c_std.rstrip().split('\n')
    with open(answer) as Fin:
        c_answer = Fin.read()
        c_answer = c_answer.rstrip().split('\n')
    if len(c_std) != len(c_answer):
        return 'File length differs', 0
    for idx, lin_std in enumerate(c_std):
        lin_ans = c_answer[idx].rstrip()
        lin_std = lin_std.rstrip()
        if lin_std != lin_ans:
            return f'Error is found at Line {idx}', 0
    return 'Correct', max_score


def judge(input_file, standard_file, exe, timeout, workdir, args, max_score=10, judger=standard_judger):
    file_name = get_random_filename() + '.out'
    output_file = os.path.join(workdir, file_name)
    exec_file = os.path.join(workdir, exe)
    Fout = open(output_file, 'w')
    Fin = open(input_file)

    with Fin:
        with Fout:
            try:
                subprocess.run(
                    [exec_file], check=True, timeout=timeout,
                    stdin=Fin, stdout=Fout
                )
            except subprocess.TimeoutExpired:
                return 'Out of Time Limit!', 0
            except subprocess.CalledProcessError as e:
                return f'Runtime Error with returncode {e.returncode}', 0
    return judger(output_file, standard_file)


if __name__ == '__main__':
    args = init_args()
    print('[INFO] Config:', args)
    workdir = tempfile.mkdtemp()

    exec_dir = os.path.join(workdir, exec_name[args.task][1])
    if (type(exec_name[args.task][0]) is str):
        main_dir = os.path.join(args.source_dir, exec_name[args.task][0])
        compile_cmd = f'g++ \"{main_dir}\" -o \"{exec_dir}\" -g -Wall --std=c++11'
    else:
        code_dir = " ".join([
            f"\"{os.path.join(args.source_dir, code_name)}\"" for code_name in exec_name[args.task][0]
        ])
        main_dir = os.path.join(args.source_dir, exec_name[args.task][0][0])
        compile_cmd = f'g++ {code_dir} -o \"{exec_dir}\" -g -Wall --std=c++11'
    if not os.path.exists(main_dir):
        print(f'[INFO] Missing Source Code')
        print('[SCORE] 0')
    else:
        cp_pro = subprocess.run(compile_cmd, shell=True)
        ret_code = cp_pro.returncode
        if ret_code != 0:
            print('[INFO] Compile Error\n[SCORE] 0')
        else:
            for i in range(5):
                input_file = os.path.join(args.input_dir, input_name[i])
                standard_file = os.path.join(args.standard_dir, output_name[i])
                if not os.path.exists(input_file):
                    print(f'[INFO] Missing Input File')
                elif not os.path.exists(standard_file):
                    print(f'[INFO] Missing Standard Output File')
                else:
                    msg, score = judge(input_file, standard_file,
                                       exec_name[args.task][1], args.timeout,
                                       workdir, args, 10, standard_judger
                                       )
                    print(
                        f'[TEST POINT {i+1}]: \n[INFO] {msg}\n[SCORE] {score}')

    shutil.rmtree(os.path.abspath(workdir), ignore_errors=True)
