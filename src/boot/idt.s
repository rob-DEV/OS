.global idt_load
.type idt_load, %function
.extern idtp
idt_load:
    lidt idtp
    ret
    