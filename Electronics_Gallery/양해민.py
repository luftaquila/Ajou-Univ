id_f = int(input('�й� ���ڸ� 4��? '))
id_s = int(input('�й� ���ڸ� 4��? '))
name = input('�̸�? ')
var = id_f * id_s - (id_f + id_s)
while var > 10 :
    var /= id_s
var = int(var)
print('���� 1 : ', var)
i = 0
while(i < var) :
    print(name, end = ' ')
    i += 1
input()
