section .text
      global sumaBinaria
  sumaBinaria:
            push ebp    
            mov ebp, esp
            sub esp, 8
            mov dword [ebp - 4], 0
            mov dword [ebp - 8], 8

            xor ecx, ecx         
primer_num  mov eax, [ ebp + 8 + 4*ecx ]        
            sub eax, 48
            mul dword [ebp - 8]
            shr dword [ebp - 8], 1
            add [ebp - 4], eax
            inc ecx      
            cmp ecx, 3    
            jle primer_num   

            mov dword [ebp - 8], 8
            xor ecx, ecx
segundo_num mov eax, [ ebp + 24 + 4*ecx]        
            sub eax, 48
            mul dword [ebp - 8]
            shr dword [ebp - 8], 1
            add [ebp - 4], eax
            inc ecx      
            cmp ecx, 3    
            jle segundo_num   

            mov eax, [ebp - 4]
            
            mov esp, ebp
            pop ebp     
            ret