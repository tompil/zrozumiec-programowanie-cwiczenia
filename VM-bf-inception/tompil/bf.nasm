;brainfuck interpreter in gynvael coldwind's assembler
;r0 - address of current place of code
;r1 - address of begin memory
;r2 - current place in memory
;r3 - 0
;r4 - temporary variable
;r5 - temporary variable
;r6 - temporary variable
%include "vm.inc"

vset r0, memory

vset r4, read
vcrl 0x109, r4

vset r4, 1
vcrl 0x110, r4
voutb 0x22, r4
vset r3, 0xa
infloop:
  vjmp infloop
  
read:
	vinb 0x20, r5
	vcmp r5, r3
	vjz execute
	vstb r0, r5
	vadd r0, r4
	vjmp read
	
execute:
	vxor r3, r3
	vcrl 0x110, r3
	vmov r1, r0
	vmov r2, r0
	vset r0, memory
	vset r3, 1 ; and since now r3 will be 1
	
execute_loop:
	vcmp r0, r1
	vje end
	vldb r4, r0
	vset r5, '>'
	vcmp r4, r5
	vje next_cell
	vset r5, '<'
	vcmp r4, r5
	vje prev_cell
	vset r5, '+'
	vcmp r4, r5
	vje incr_val
	vset r5, '-'
	vcmp r4, r5
	vje decr_val
	vset r5, ','
	vcmp r4, r5
	vje read_byte
	vset r5, '.'
	vcmp r4, r5
	vje write_byte
	vset r5, '['
	vcmp r4, r5
	vje begin_loop
	vset r5, ']'
	vcmp r4, r5
	vje end_loop
	after_switch:
	vadd r0, r3
	vjmp execute_loop
	
next_cell:
	vadd r2, r3
	vjmp after_switch

prev_cell:
	vsub r2, r3
	vcmp r2, r1
	vjb end
	vjmp after_switch

incr_val:
	vldb r4, r2
	vadd r4, r3
	vstb r2, r4
	vjmp after_switch

decr_val:
	vldb r4, r2
	vsub r4, r3
	vstb r2, r4
	vjmp after_switch
	
write_byte:
	vldb r4, r2
	voutb 0x20, r4
	vjmp after_switch
	
read_byte:
	vinb 0x21, r4
	vcmp r4, r3
	vjne no_input
	get_input:
	vinb 0x20, r4
	vstb r2, r4
	vjmp after_switch
	no_input:
		vmov r5, sp
		vset r4, new_input
		vcrl 0x109, r4
		vset r4, 1
		vcrl 0x110, r4
		voutb 0x22, r4
		vjmp infloop
	new_input:
		vset r4, 0
		vcrl 0x110, r4
		vmov sp, r5
		vjmp get_input
	
begin_loop:
	vset r4, 0
	vldb r6, r2
	vcmp r6, r4
	vje out_of_bloop
	vpush r0
	vjmp after_switch
	out_of_bloop:
		vmov r4, sp
		vset r6, '['
		vset r7, ']'
		loop:
			vadd r0, r3
			vcmp r0, r1	
			vje end
			vldb r8, r0
			vcmp r8, r6
			vje open_loop_found
			vcmp r8, r7
			vje end_loop_found
			vjmp loop
		open_loop_found:
			vpush r0
			vjmp loop
		end_loop_found:
			vcmp r4, sp
			vjmp after_switch
			vpop r8
			vjmp loop
		
end_loop:
	vxor r4, r4
	vldb r6, r2
	vcmp r6, r4
	vje out_of_eloop
	vmov r6, sp
	vld r0, r6
	vjmp after_switch
	out_of_eloop:
		vpop r4
		vjmp after_switch
		
end:
	voff
	
memory:
