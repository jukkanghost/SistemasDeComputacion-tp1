section .text
      global restaDecimal
  restaDecimal:
      push ebp    
      mov ebp, esp
 
      mov eax, [ ebp + 8 ]        
      sub eax, [ ebp + 12 ]
 
      pop ebp     
      ret