id_f = int(input('학번 앞자리 4개? '))
id_s = int(input('학번 뒷자리 4개? '))
name = input('이름? ')
var = id_f * id_s - (id_f + id_s)
while var > 10 :
    var /= id_s
var = int(var)
print('변수 1 : ', var)
i = 0
while(i < var) :
    print(name, end = ' ')
    i += 1
input()
