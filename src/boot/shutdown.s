.global shutdown
.type shutdown, %function

shutdown:
  hlt
 
  ret  //if interrupt doesnt work

  // mov $0x10, %ax
  // mov %ax, %ds