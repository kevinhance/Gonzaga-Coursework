
#Student Name: Kevin Hance
#Zagmail Address: khance@zagmail.gonzaga.edu
#CPSC 475 Final Project: Test 3C
#	This individual final project involves the implementation of the CYK parser
# Completed: 12/13/2018
# Due:       12/14/2018

import re
import sys

def main():

    # store number of arguments to ensure proper user input
    argNum = len(sys.argv)

    # get int arguments from script call into list (ensure correct # of arguments)
    if(argNum < 3):
        print('Please enter 2 flienames for the grammar and string files, respectively')
        exit(1)
    
    # set filenames to system arguments
    g_filename = sys.argv[1]
    s_filename = sys.argv[2]

    # initialize dictionary g for grammar and list s for string
    g = readGrammarToDict(g_filename)
    s = readStringToList(s_filename)

    # get the matrix and 
    x, result = produceCYKMatrix(g,s)
    print(result)

# ------------------ readGrammarToDict ------------------ #
# read grammar txt file into dictionary data structure, return dictionary

def readGrammarToDict(g_filename):
    g_fp = open(g_filename)
    rhs_delim = '|'
    g = {}
    # break grammar file into a list of lines
    g_lines = g_fp.read().splitlines()
    for line in g_lines:
        cur_line = []
        # break each line into tokens,separated by spaces
        for token in line.split():
            # add to temp list
            cur_line.append(token)
        rhs_options = []
        # left hand side of equation is just the first token
        lhs = cur_line[0]
        # second half of equation is the 3rd element to the nth element
        rhs = cur_line[2:]
        if(rhs_delim in rhs):
            for token in rhs:
                if(token != rhs_delim):
                    rhs_options.append(token)
        else:
            rhs_str = ''
            for token in rhs:
                rhs_str += token
                rhs_str += ' '
            rhs_str = rhs_str.rstrip(' ')
            rhs_options.append(rhs_str)

        # case 1
        if(lhs in g): # and g[lhs] is not None
            for option in rhs_options:
                g[lhs].append(option)

        else:
            g.update({lhs : rhs_options})
            
    return g

# ------------------ readStringToList ------------------ #
# read string txt file into a list using spaces as delimeters, return list 
def readStringToList(s_filename):
    s_fp = open(s_filename)
    s = []
    s_tokens = s_fp.read().split()
    for token in s_tokens:
        s.append(token)
    return s

# ------------------ produceCYKMatrix ------------------ #
# generate CYK matrix using grammar and string structures created using functions above
# input:    context free grammar in Chomsky normal form (g), list of words/tokens from input string (s)
# output:   completed CYK matrix (x) and either 'Yes' or 'No' based on whether or not the input string
#           is valid in the given grammar (result)

def produceCYKMatrix(g, s):
    # initialize variables
    xDim = len(s)
    x = []
    i = 0
    j = 0

    # 1. initialize all X(i,j) to {}
    while(i <= xDim):
        xRow = []
        j = 0
        while(j <= xDim):
            xRow.append([])
            j += 1
        x.append(xRow)
        i += 1

    # 2. for each variable (lhs), if there is a rule lhs -> 
    i = 1
    j = 0
    while(i <= xDim):
        for lhs in g:
            if (s[i-1] in g[lhs]):
                x[i][i].append(lhs)
        i += 1

    # 3. for each step 2 to n
    step = 2
    i = 0
    k = 0
    while(step <= xDim):
        i = 1
        while(i <= (xDim - step + 1)):
            k = i
            while(k <= i + step - 2):
                B = x[i][k]
                C = x[k+1][i +step -1]
                bcList = []
                for bRule in B:
                    for cRule in C:
                        bcStr = bRule + ' ' + cRule
                        bcList.append(bcStr)
                        for lhs in g:
                            for bc in bcList:
                                if bc in g[lhs]:
                                    if (lhs not in x[i][i+step-1]):
                                        x[i][i+step-1].append(lhs)

                k += 1
            i += 1
        step += 1

    # 4. check X[1][n] for start value S to see if sentence is in the lexicon
    isInLexicon = ''
    if 'S' in x[1][xDim]:
        isInLexicon = 'Yes'
    else:
        isInLexicon = 'No'

    # return matrix and boolean
    return x, isInLexicon

# ------------------ print Matrix ------------------ #
# prints matrix in a format that makes it slightly easier to read

def printMatrix(mat):
    print('\t')
    curLine = ''
    for col in mat:
        curLine = ''
        for elem in col:
            curLine += ('\t' + str(elem))
        print(curLine)

#####################

main()