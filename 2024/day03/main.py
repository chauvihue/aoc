import re
s = ''
res = 0

class part1:
    def solve():
        global res
        l = re.findall('mul\(\d+\,\d+\)', s)
        for op in l:
            num = re.findall('\d+', op);
            res += int(num[0])*int(num[1])
        print(res)

class part2:
    def solve():
        global res
        l = [t[0]+t[1]+t[2] for t in re.findall("(mul\(\d+\,\d+\))|(do\(\))|(don't\(\))", s)]
        ok = True
        print(l)
        for op in l:
            if op == "do()": ok = True
            elif op == "don't()": ok = False
            elif ok:
                num = re.findall('\d+', op);
                res += int(num[0])*int(num[1])
        print(res)

if __name__ == "__main__":
    with open('day03\input.txt', 'r') as f:
        s = f.read()
    part1.solve()