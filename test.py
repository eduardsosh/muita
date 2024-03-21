import filecmp
import sys

def compare_files(file1, file2):
    if filecmp.cmp(file1, file2):
        print("Pass")
    else:
        print("Fail")

def main():
    if len(sys.argv) != 3:
        print("Usage: python script.py <file1> <file2>")
        sys.exit(1)

    file1 = sys.argv[1]
    file2 = sys.argv[2]

    compare_files(file1, file2)

if __name__ == "__main__":
    main()
