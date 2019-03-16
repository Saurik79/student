include console.inc
                                  
.code
start:
    outstr 'Enter your number'
    outchar ' '
    inint ecx
    mov eax,ecx
    nextnumber:       ;Работаем с новыи числом
        mov eax,ecx 
        mov ebx,3     ;Устанавливаем делитель на 3
        mov edx,0     ;Так же зануляем dx
        div ebx       ;Производим деление
        mov ebx,0     
        add ebx,edx   ;Делаем проверку на деление без остатка
        jz check35    ;Если делится без остатка - переходим к другой проверке
        jnz  check5   ;Если с остатком - проверить осталось на 5
    check35:
        mov eax,ecx   ;Если на 3,  проверим на 5
        mov ebx,5
        mov edx,0
        div ebx
        mov ebx,0
        add ebx,edx
        jz write3n5
        jnz write3     
    write3n5:                       ;На 3 и на 5 - выпишем
        outint ecx
        outchar ' '
        outstrln 'FizzBuzz'
        dec ecx
        jnz nextnumber
        jz finish
    write3:                         ;Только 3 - выпишем
        outint ecx
        outchar ' '
        outstrln 'Fizz'
        dec ecx
        jnz nextnumber
        jz finish  
    check5:                         ;Если не на 3 - проверим на 5
        mov eax,ecx     
        mov ebx,5
        mov edx,0 
        div ebx
        mov eax,0
        add eax,edx
        jz write5
        jnz nothing
    nothing:                        ;Не делится не на 5, не на 3 
        dec ecx
        jnz nextnumber
        jz finish  
    write5:                         ;Выпишем на 5
        outint ecx
        outchar ' '
        outstrln 'Buzz'
        dec ecx
        jnz nextnumber
        jz finish         
    finish:
        exit 
    end start 
        
