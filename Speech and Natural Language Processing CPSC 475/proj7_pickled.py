import re
import sys
import random
import nltk
from nltk.corpus import brown
from decimal import *

def main():
	# set precision of probablility decimals
	getcontext().prec = 10
	# set tmp to all editorial sentences from the brown corpus
	tmp = brown.sents(categories='editorial')
	# encode all unicode tokens into ascii
	uniList = [[item.encode('ascii') for item in lst] for lst in tmp]
	# remove periods, commas, exclamation and question marks
	uniList = removeMetachars(uniList)
	# remove empty strings and any words that don't
	# have a single alphabetic character in them
	uniList = removeNonWords(uniList)
	# count number of words in corpus
	wordCount = countWords(uniList)
	bigramCount = wordCount - 1
	trigramCount = wordCount - 2
	quadgramCount = wordCount - 3
	# create corpus of bigrams, trigrams, and quadgrams
	biList = makeBigrams(uniList)
	print(biList)
	#triList = makeTrigrams(uniList)
	#quadList = makeQuadgrams(unilist)
	# initialize dictionaries
	prob = {}
	cumProb = {}

	biProb = {}
	biCumProb = {}
	
	triProb = {}
	triCumProb = {}

	quadProb = {}
	quadCumProd  = {}
	# calculate probabilities & populate dictionaries with data
	prob = calculateProbabilities(uniList, prob)
	cumProb = calculateCumulativeProbabilities(prob)



	# generate and print sentences
	#i = 0
	#while(i<5):
	#	print(generateSentence(cumProb, prob, wordCount))
	#	i += 1
	
def removeMetachars(words):
	# for each word, replace periods with the empty string
	i = 0
	j = 0
	for lst in words:
		for item in lst:
			words[i][j] = re.sub(r'[.,!?]', '', item).lower()
			j+=1
			
		i+=1
		j=0
	return words

def removeNonWords(words):
	# removes non-words (strings without any alphabetic characters
	# to Dr. DePalma: I know you didn't ask us to do this in the project
	# specifications, but I noticed that after removing metachars, there were
	# over 6,500 strings in the corpus with no letters. Most of these were
	# empty strings. So I took the liberty of removing these "non-words", as
	# some of my sentences would appear to only have 5 words, since 5 of them
	# were empty strings
	i = 0
	j = 0
	for lst in words:
		for item in lst:
			if(None == re.match(r'[a-z]', item) or item == ''):
				del words[i][j]
				j-=1
			j+=1
		i+=1
		j=0
	return words

def removeNonWords(words):
	
	for lst in words:
		for item in lst:
			if(None == re.match(r'[a-z]', item) or item == ''):
				del words[i][j]
				j-=1
			j+=1
		i+=1
		j=0
	return words
	

def countWords(words):
	# count number of words in corpus
	num = 0
	for lst in words:
		for item in lst:
			num+=1
	return num

def makeBigrams(words):
	startStr = '<s>'
	endStr = '</s>'
	lastWord = startStr
	biList = []
	i = 0
	j = 0
	for lst in words:
		for item in lst:
			#add lastWord + item to biList
			biList.append(lastWord + ' ' + item)
			lastWord = item
			j+=1
		i+=1
		j=0
	biList.append(lastWord + endStr)
	return biList

def calculateProbabilities(words, dic):
	# populate dictionary with probabilities
	lastWord = '<s>'
	for lst in words:
		for item in lst:
			if item in dic:
				dic.update({item : dic[item] + 1})
			else:
				dic.update({item : 1})
	return dic

def calculateCumulativeProbabilities(dic):
	# populate dictionary with cumulative probabilities
	cumulativeDic = {}
	currProb = 0
	for item in dic:
		currProb += dic[item]
		cumulativeDic.update({item : currProb})
	return cumulativeDic

def getWordProb(target, dic, wordCount):
	# return number of instances divided by total word count
	if(target in dic):
		return Decimal(dic[target]) / Decimal(wordCount)
	else:
		return -1
	
def getCumulativeWordProb(target, cumulativeDic, wordCount):
	# return cumulative number of instances divided by total word count
	if(target in cumulativeDic):
		return Decimal(cumulativeDic[target]) / Decimal(wordCount)
	else:
		return -1
	
def generateSentence(dic, dic2, wordCount):
	# generate sentences using Bogensberger-Johnson Cumulative Probability Technique
	randNum = 0
	i = 0
	sentence = ''
	currWord = ''
	while(i < 10):
		randNum = Decimal(random.random())
		for item in dic2:
			if(getCumulativeWordProb(item, dic, wordCount) > randNum):
				currWord = item
				if(i == 0):
					# if this is the first word of the sentence, capitalize it
					currWord = currWord.capitalize()
				else:
					# otherwise, place a space before the start of the word
					sentence += ' '
				sentence += currWord
				break
		i += 1
	sentence += '.'
	return sentence

####################################################################################

main()
