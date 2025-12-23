# xv6 RISC-V core concepts glossary
⸻

1. Memory & Addressing
	•	Physical/Virtual Address/Memory
	•	Physical/Virtual Address Space
	•	Page
	•	Page Size (PGSIZE)
	•	Page Table
	•	Page Table Entry (PTE)
	•	Address Translation
	•	Memory Mapping
	•	Identity Mapping
	•	MMIO (Memory-Mapped I/O)

⸻

2. Program & Process
	•	ELF (Executable and Linkable Format)
	•	Process Address Space
	•	Process Isolation
	•	Copy-on-Write (COW)
	•	Process Context
	•	CPU Context
	•	Context Switch

⸻

3. Binary Layout (ELF / Image)
	•	Text Segment (.text)
	•	Read-Only Data (.rodata)
	•	Initialized Data (.data)
	•	Uninitialized Data (.bss)
	•	Symbol Table
	•	Debug Sections
	•	Entry Point
	•	Linker Script
	•	Load Address
	•	Relocation

⸻

4. Runtime Memory
	•	Stack
	•	Stack Frame
	•	Stack Pointer (SP)
	•	Heap
	•	Dynamic Memory Allocation
	•	malloc / free
	•	sbrk
	•	Guard Page
	•	User Stack
	•	Kernel Stack

⸻

5. Kernel-Specific Concepts
	•	Kernel Space
	•	User Space
	•	Kernel Virtual Address
	•	Kernel Mapping
	•	Trap
	•	Trapframe
	•	Trampoline
	•	System Call
	•	Interrupt
	•	Exception
	•	Privilege Level
	•	User Mode
	•	Supervisor Mode
	•	Machine Mode

⸻

6. Boot & Hardware (RISC-V / QEMU)
	•	Boot ROM
	•	Bootloader
	•	Entry Code (entry.S)
	•	CLINT (Core Local Interruptor)
	•	PLIC (Platform-Level Interrupt Controller)
	•	UART
	•	VirtIO
	•	Device Register
	•	Hardware Thread (Hart)

⸻

7. RISC-V / CPU Concepts
	•	Instruction Pointer / Program Counter (PC)
	•	General-Purpose Registers
	•	Calling Convention
	•	ABI (Application Binary Interface)
	•	Trap Vector
	•	CSR (Control and Status Register)
	•	ecall
	•	Privilege Transition

⸻

8. Memory Management (Kernel View)
	•	Physical Page Allocator
	•	Free List
	•	Page Fault
	•	Demand Paging
	•	Lazy Allocation
	•	Kernel Page Table
	•	User Page Table
	•	TLB (Translation Lookaside Buffer)

⸻

9. Toolchain & Build
	•	Compiler
	•	Assembler
	•	Linker
	•	Object File (.o)
	•	Static Linking
	•	Cross Compiler
	•	objdump
	•	nm
	•	readelf

⸻

10. Mental Models（very important）
	•	“Process = Virtual Memory + CPU Context”
	•	“Fork duplicates an address space”
	•	“Exec replaces the address space”
	•	“Stack grows downward”
	•	“Heap grows upward”
	•	“Everything is an address”
	•	“User programs never see physical memory”

⸻

⸻

Assembly & OS Glossary (English, with Abbreviations)

⸻

1. Instruction & Control Flow

Instruction
	•	Meaning: A single operation executed by the CPU.
	•	Scope: Smallest unit of execution.

⸻

Load / Store
	•	Load: Memory → Register
	•	Store: Register → Memory
	•	Reason: RISC architectures only access memory via load/store.

⸻

ADDI
	•	Full name: Add Immediate
	•	Meaning: rd = rs + immediate
	•	Usage: Stack pointer adjustment, address calculation.

⸻

JAL
	•	Full name: Jump And Link
	•	Meaning: Jump to target and save return address in ra.

⸻

JALR
	•	Full name: Jump And Link Register
	•	Meaning: Indirect jump via register.

⸻

RET
	•	Meaning: Return from function
	•	Reality: Pseudo-instruction for jalr x0, ra, 0.

⸻

Branch
	•	Meaning: Conditional control-flow change
	•	Examples: beq, bne, blt, bge

⸻

2. Registers & ABI Terms

Register
	•	Meaning: CPU internal storage holding execution state.

⸻

GPR
	•	Full name: General Purpose Register
	•	Meaning: Registers used for computation and data movement.

⸻

RA
	•	Full name: Return Address
	•	Meaning: Stores address to return to after a function call.

⸻

SP
	•	Full name: Stack Pointer
	•	Meaning: Points to the top of the current stack frame.

⸻

Caller-Saved Registers
	•	Meaning: Must be saved by the caller if needed after a call.
	•	RISC-V: t0–t6, a0–a7

⸻

Callee-Saved Registers
	•	Meaning: Must be preserved by the callee.
	•	RISC-V: s0–s11

⸻

ABI
	•	Full name: Application Binary Interface
	•	Meaning: Binary-level contract defining calling conventions, data layout, and register usage.

⸻

3. Control and Status Registers (CSR)

CSR
	•	Full name: Control and Status Register
	•	Meaning: Special registers controlling CPU mode and state.

⸻

SATP
	•	Full name: Supervisor Address Translation and Protection
	•	Meaning: Points to the current page table (defines address space).

⸻

SEPC
	•	Full name: Supervisor Exception Program Counter
	•	Meaning: Saved PC to return to after trap.

⸻

SCAUSE
	•	Full name: Supervisor Cause
	•	Meaning: Reason why a trap occurred.

⸻

STVEC
	•	Full name: Supervisor Trap Vector
	•	Meaning: Address of trap entry code.

⸻

4. Trap / Privilege Model

Trap
	•	Meaning: Forced transfer of control to the kernel.
	•	Causes: System call, exception, interrupt.

⸻

Exception
	•	Meaning: Synchronous trap caused by executing an instruction.
	•	Example: Page fault, illegal instruction.

⸻

Interrupt
	•	Meaning: Asynchronous trap caused by external events.
	•	Example: Timer, device interrupt.

⸻

ECALL
	•	Full name: Environment Call
	•	Meaning: Instruction to request kernel service (system call).

⸻

SRET
	•	Full name: Supervisor Return
	•	Meaning: Return from supervisor mode to user mode.

⸻

Trap Handler
	•	Meaning: Code that handles traps.
	•	xv6: uservec (assembly) → usertrap() (C)

⸻

5. Stack & Context

Stack
	•	Meaning: Memory region holding execution history (call frames).

⸻

Stack Frame
	•	Meaning: Per-function execution record on the stack.

⸻

Prologue
	•	Meaning: Function entry code saving necessary state.

⸻

Epilogue
	•	Meaning: Function exit code restoring state.

⸻

Context
	•	Meaning: Minimal CPU state required to resume execution.

⸻

Context Switch
	•	Meaning: Saving one context and restoring another.

⸻

SWTCH
	•	Meaning: xv6 assembly routine performing context switch.

⸻

6. Memory & Addressing

PC
	•	Full name: Program Counter
	•	Meaning: Address of the current instruction.

⸻

Virtual Address (VA)
	•	Meaning: Address used by the program.

⸻

Physical Address (PA)
	•	Meaning: Actual memory hardware address.

⸻

Page Table
	•	Meaning: Mapping rules from VA → PA.

⸻

Address Space
	•	Meaning: The set of addresses a program can see and use.

⸻

Trampoline
	•	Meaning: Fixed-mapped assembly code used to transition between user and kernel modes.

⸻

7. Process & Execution Structures

Trapframe
	•	Meaning: Saved user-mode CPU state at the moment of a trap.

⸻

Context (struct context)
	•	Meaning: Kernel-only saved state used by the scheduler.

⸻

Kernel Stack
	•	Meaning: Stack used while executing kernel code.

⸻

8. Binary & Linking

ELF
	•	Full name: Executable and Linkable Format
	•	Meaning: Standard binary format for executables and object files.

⸻

Symbol
	•	Meaning: Named address (function or variable).

⸻

Relocation
	•	Meaning: Process of fixing symbol addresses at link/load time.

⸻

Entry Point
	•	Meaning: Address where execution starts.
	•	xv6 user programs: start

⸻

9. Core xv6 Keywords (Minimal Set)

Term	Meaning
ABI	Binary calling and data contract
Trapframe	Full saved user execution state
Context	Minimal state for rescheduling
Trampoline	Mode-switching assembly bridge
SATP	Defines current address space
SRET	Return to user mode


⸻

10. How to Use This Glossary

When reading xv6 or assembly:
	•	Instruction → “state change or control-flow change?”
	•	Register → “short-lived or long-lived state?”
	•	Save/Restore → “what consistency is being preserved?”

If you can answer those three questions, this glossary is sufficient.