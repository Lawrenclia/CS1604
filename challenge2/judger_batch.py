import time
import random
import os
import subprocess
import argparse
import sys
import shutil
import tempfile

exec_name = {
    '1_advanced_a_b': ['main.cpp', 'advanced_a_b']
}


# exec_name: {'task_name': ['main.cpp', 'executeable']}

# absoulte path of the current directory
def get_thisdir():
    return os.path.dirname(os.path.abspath(
        sys.executable if getattr(sys, 'frozen', False) else __file__
    ))


def get_cs1604_path(cs1604_txt):
    # cs1604_txt = os.path.join(thisdir, 'source', 'cs1604.txt')
    try:
        f = open(cs1604_txt,encoding='utf-8')
    except FileNotFoundError:
        print(
            'error: to use StanfordCppLib, you must create a text file',
            cs1604_txt,
            'whose contents is the absolute path '
            'to the compiled StanfordCppLib.',
            sep='\n', file=sys.stderr
        )
        sys.exit(1)
    with f:
        s = f.read().strip()
    if not os.path.isabs(s):
        print(
            'error: the path to StanfordCppLib must be an absolute path, but',
            s,
            'is supplied, which is not an absolute path.',
            sep='\n', file=sys.stderr
        )
        sys.exit(1)
    return s

# uniform test point names for each task
input_name = ['1.in', '2.in', '3.in' , '4.in', '5.in', '6.in', '7.in', '8.in' , '9.in', '10.in' ]
output_name = ['1.out', '2.out', '3.out' , '4.out', '5.out', '6.out', '7.out', '8.out' , '9.out', '10.out' ]

def init_args():
    parser = argparse.ArgumentParser('Judger For Homework 4')
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
        help='the folder containing the soruce code'
    )
    parser.add_argument(
        '--timeout', default=2, type=float,
        help='the timeout for judging (in seconds), default is 2'
    )

    args = parser.parse_args()

    # set the directories of input, output and source code
    if args.input_dir is None:
        args.input_dir = os.path.join('data',args.task)
    if args.standard_dir is None:
        args.standard_dir = os.path.join('data',args.task)
    if args.source_dir is None:
        args.source_dir = args.task
 
        
    thisdir = get_thisdir()
    # get the include and lib path from cs1604.txt in the source dir
    cs1604_txt = os.path.join(thisdir, 'source', 'cs1604.txt')
    if os.path.exists(cs1604_txt):
        cs1604_path = get_cs1604_path(cs1604_txt)
        args.cs1604_cxxargs = [f'-I{os.path.join(cs1604_path, "include")}']
        args.cs1604_ldargs = [
            f'-L{os.path.join(cs1604_path, "lib")}', '-lCS1604'
        ]
    else:
        args.cs1604_cxxargs = []
        args.cs1604_ldargs = []

    return args


def get_random_filename():
    lst = []
    for x in range(10):
        lst.append(chr(ord('A') + random.randint(0, 25)))
    temp_path = ''.join(lst)
    return temp_path


def standard_judger(answer, std, max_score=10):
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
            error_message = f'Wrong answer found at Line {idx + 1}'
            return error_message, 0
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

forbid_map = {'1_area' : [ "Vector", "vector", "Stack", "stack", "Queue", "queue", "Map", "map" ],
              '2_regex' : ["string", "String", "regex", "Vector", "vector", "Stack", "stack", "Queue", "queue", "Map", "map"],
              '3_register' : ["Vector", "vector", "Stack", "stack", "Queue", "queue"]}

def check_forbid(args, main_dir):
    if args.task in forbid_map:
        forbid_list = forbid_map[args.task]
        with open(main_dir, 'rb') as f:
            for l in f.readlines():
                for keyword in forbid_list:
                    if l.find(b"include") != -1:
                        pos = l.find(bytes(keyword, 'utf-8'))
                        if pos != -1:
                            # whitelist : cstring
                            found = False
                            if keyword == 'string':
                                while pos > 0:
                                    if l[pos-1] == 99 or l[pos-1] == 67:
                                        pos = l.find(bytes(keyword, 'utf-8'), pos + 1)
                                        continue
                                    else:
                                        found = True
                                        break
                            else:
                                found = True
                            if found:
                                print(f'[INFO] #include "{keyword}" is forbidden in {args.task}')
                                print('[SCORE] 0')
                                return True
    return False

if __name__ == '__main__':
    args = init_args()
    print('[INFO] Config:', args)
    workdir = tempfile.mkdtemp()

    main_dir = os.path.join(args.source_dir, exec_name[args.task][0])
    exec_dir = os.path.join(workdir, exec_name[args.task][1])

    compile_cmd = ['g++', main_dir, '-o', exec_dir, '-g', '-Wall', '--std=c++11'] + args.cs1604_cxxargs + args.cs1604_ldargs
    # [f'g++ \"{main_dir}\" -o \"{exec_dir}\" -g -Wall --std=c++11'] + args.cs1604_cxxargs + args.cs1604_ldargs

    if not os.path.exists(main_dir):
        print(f'[INFO] Missing Source Code')
        print('[SCORE] 0')
    else:
        # check whether container is used
        if check_forbid(args, main_dir):
            exit(-1)
        cp_pro = subprocess.run(compile_cmd)
        ret_code = cp_pro.returncode
        if ret_code != 0:
            print('[INFO] Compile Error\n[SCORE] 0')
            # print(cp_pro.args)
        else:
            for i in range(10):
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
                    print(f'[TEST POINT {i+1}]: \n[INFO] {msg}\n[SCORE] {score}')
                    
    shutil.rmtree(os.path.abspath(workdir), ignore_errors=True)
