# function to find all permutation of string [1..n]
def permute(n):
    # string contains ordered sequence of number from 1 to n
    string = [i+1 for i in range(n)] 

    # count contains frequencies of each number
    count = [1 for i in range(n)]

    # result is array of result (one sequence)
    result = [0 for x in range(n)]

    # ret is count of total sequence
    ret = permute_util(string, count, result, 0)
    print(ret)

# function helper that do backtracking 
# to find next permutation of string
# level means depth of recursion / dfs tree
def permute_util(string, count, result, level):
    if level == len(result):
        # print(result)
        return 1

    ret = 0
    # find the first character from the left
    # which its frequencies is non zero
    for i in range(len(string)):
        if count[i] == 0:
            continue;

        # put the character to result according to its level
        result[level] = string[i]
        # decrease its frequencies
        count[i] -= 1
        # do permutation again but with new result and new level
        ret += permute_util(string, count, result, level + 1)

        # increase back character's frequencies
        count[i] += 1
    return ret

if __name__ == '__main__':
    n = input();
    permute(int(n))