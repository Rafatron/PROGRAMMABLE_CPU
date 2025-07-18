compilation: 
CPU.c and assembler.c απαιτείται!

επειτα χρησιμοποιούνται στην γραμμή εντολών πχ windows (same directory):
./assembler 1 filename.asmm
./CPU 1 filename.lc

Το 1 δηλώνει το πλήθος των arguments (δεν το έχω κάνει να λειτουργεί για πάνω από ένα, μου επιβάλλει την παράμετρο αυτή η C).
Τα αρχεία 'assembly' μπορούν να έχουν ό,τι κατάληξη επιθυμεί ο χρήστης, αλλά κατά τη μεταγλώττιση το αρχείο εξόδου έχει επέκταση .lc.

#######################
#######################

==ARITHMETIC==
ADD 0001 out in1 in2  //output registry, input registry, input registry
SUB 0010 out in1 in 2 //output registry, input registry, input registry

==LOGIC==
AND 0011 out in1 in2  //output registry, input registry, input registry
OR  0100 out in1 in2  //output registry, input registry, input registry
XOR 0101 out in1 in2  //output registry, input registry, input registry
NOT 0110 out in       //output registry, input registry

==CONTROL FLOW==
MOV 0111 val reg      // 8 bit number, storing registry
JMP  1000 line        //jump to line on text editor (assuming text editor index starts at 1)
JPN  1001 line        //jump if last operation (arithmetic || logic) resulted in zero
JPNZ 1010 line        //jump if last operation (arithmetic || logic) did not result in zero

==MISC==
CMP  1011 out in1 in2 //output registry, input registry, input registry, outputs 0 if in1==in2, 1 if in1>in2, 2if in1<in2
NOP  1100             //do nothing 

==STACK==
PUSH 1101 value    //push value  onto stack
POP  1110          //pop value from stack
PREG 1111 reg      //push register onto stack

==FLAGS==
Z zero flag 1 if last operation ==0
J jump flag, tells program counter to not proceed after jumping

==SPECS==
16 registers of 8 bits
20 bit instructions 
1024 instructions
registry 15 stack pointer (value)

==INSTRUCTION BREAKDOWN==
4 opcode  first 4 bits
8 arg1     later 8 bits
4 arg2     later 4 bits
4 arg3     last 4 birs
1 /0 null string terminator

###########################
##########################

παράδειγμα προγράμματος πρόσθεσης:
MOV 5 0;      //φορτωσε στο registry 0 την τιμη 5
MOV 6 1;      //φορτωσε στο registry 1 την τιμη 6
;             //καινή γραμμή 
ADD 2 0 1;    //φόρτωσε στο registry 2 την τιμη 5+6
EOF;          //end of file ΑΠΑΡΑΙΤΗΤΟ

δίνονται ετοιμα αρχεια .asmm (fibbonachi.asmm, calculator.asmm)