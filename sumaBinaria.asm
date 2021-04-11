section .text
      global sumaBinaria
  sumaBinaria:
      push ebp    
      mov ebp, esp
 
      mov eax, [ ebp + 8 ]        
      or eax, [ ebp + 12 ]

      pop ebp     
      ret
