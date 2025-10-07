import random
def main():
    writeQueryToFile(10000)
    writeQueryToFile(100000)
    writeQueryToFile(1000000)

def writeQueryToFile(a):
    f = open("hw10-data-" + str(a) + ".sql", "w")
    title = ["engineer", "salesperson", "administrator", "manager"]
    arrayCounter = 0
    i = 0
    f.write("INSERT INTO Employee VALUES")
    while (i < a):
        randSalary = random.randint(12000, 150000)
        f.write("(" + str(i) + "," + str(randSalary) + "," + "'" + title[arrayCounter] + "'" + ")")
        if(i != (a - 1)):
            f.write("," + "\n")
        arrayCounter += 1
        arrayCounter = arrayCounter % 4
        i += 1
    f.write(";")
    f.close()

main()

        