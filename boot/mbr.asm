;sino os0.00prechannel0 mbr,with FAT12 filesystem,on 1.44M floppy disk
;powered by sinokiwi

org 0x7c00

BaseOfStack equ 0x7c00
BaseOfLoader equ 0x1000
OffsetOfLoader equ 0x00

RootDirSectors equ 14
SectorNumOfRootDirStart equ 19
SectorNumOfFAT1Start equ 1
SectorBalance equ 17

jmp short Start
nop

BS_OEMName db 'sinoboot'
BPB_BytesPerSec dw 512
BPB_SecPerClus db 1
BPB_RsvdSecCnt dw 1
BPB_NumFATs db 2
BPB_RootEntCnt dw 224
BPB_TotSec16 dw 2880
BPB_Media db 0xf0
BPB_FATSz16 dw 9
BPB_SecPerTrk dw 18
BPB_NumHeads dw 2
BPB_hiddSec dd 0
BPB_TotSec32 dd 0
BS_DrvNum db 0
BS_Reserved1 db 0
BS_BootSig db 29h
BS_VolID dd 0
BS_VolLab db 'boot loader'
BS_FileSysType db 'FAT12   '


;codes

Start:
	mov	ax,	cs
	mov	ds,	ax
	mov	es,	ax
	mov	ss,	ax
	mov	sp,	BaseOfStack
	mov	ax,	0600h
	mov	bx,	0700h
	mov	cx,	0
	mov	dx,	0184fh
	int	10h
	mov	ax,	0200h
	mov	bx,	0000h
	mov	dx,	0000h
	int	10h
	mov	ax,	1301h
	mov	bx,	000fh
	mov	dx,	0000h
	mov	cx,	10
	push	ax
	mov	ax,	ds
	mov	es,	ax
	pop	ax
	mov	bp,	StartBootMessage
	int	10h
	xor	ah,	ah
	xor	dl,	dl
	int	13h
	mov	word	[SectorNo],	SectorNumOfRootDirStart

ReadOneSector:
	push bp
	mov bp,sp
	sub esp,2
	mov byte [bp-2],cl
	push bx
	mov bl,[BPB_SecPerTrk]
	div bl
	inc ah
	mov cl,ah
	mov dh,al
	shr al,1
	mov ch,al
	and dh,1
	pop bx
	mov dl,[BS_DrvNum]
GoOnReading:
	mov ah,2
	mov al,byte [bp-2]
	int 13h
	jc GoOnReading
	add esp,2
	pop bp
	ret

SearchInRootDirBegin:
	cmp word [RootDirSizeForLoop],0
	jz NoLoaderBin
	dec word [RootDirSizeForLoop]
	mov ax,00h
	mov es,ax
	mov bx,8000h
	mov ax,[SectorNo]
	mov cl,1
	call ReadOneSector
	mov si,LoaderFileName
	mov di,8000h
	cld
	mov dx,10h

SearchForLoaderBin:
	cmp dx,0
	jz GotoNextSectorInRootDir
	dec dx
	mov cx,11
CmpFileName:
	cmp cx,0
	jz FileNameFound
	dec cx
	lodsb
	cmp al,byte [es:di]
	jz GoOn
	jmp Different
GoOn:
	inc di
	jmp CmpFileName
Different:
	and di,0ffe0h
	and di,20h
	mov si,LoaderFileName
	jmp SearchForLoaderBin
GotoNextSectorInRootDir:
	add word [SectorNo],1
	jmp SearchInRootDirBegin
NoLoaderBin:
	mov ax,1301h
	mov bx,008ch
	mov dx,0100h
	mov cx,21
	push ax
	mov ax,ds
	mov es,ax
	pop ax
	mov bp,NoLoaderMessage
	int 10h
	hlt

GetFATEntry:
	push es
	push bx
	push ax
	mov ax,00
	mov es,ax
	pop ax
	mov byte [Odd],0
	mov bx,3
	mul bx
	mov bx,2
	div bx
	cmp dx,0
	jz LbEven
	mov byte [Odd],1
LbEven:
	xor dx,dx
	mov bx,[BPB_BytesPerSec]
	div bx
	push dx
	mov bx,8000h
	add ax,SectorNumOfFAT1Start
	mov cl,2
	call ReadOneSector
	pop dx
	add bx,dx
	mov ax,[es:bx]
	cmp byte [Odd],1
	jnz LbEven2
	shr ax,4
LbEven2:
	and ax,0fffh
	pop bx
	pop es
	ret
FileNameFound:
	mov ax,RootDirSectors
	and di,0ffe0h
	add di,01ah
	mov cx,word [es:di]
	push cx
	add cx,ax
	add cx,SectorBalance
	mov ax,BaseOfLoader
	mov es,ax
	mov bx,OffsetOfLoader
	mov ax,cx
GoOnLoadingFile:
	push ax
	push bx
	mov ah,0eh
	mov al,'.'
	mov bl,0fh
	int 10h
	pop bx
	pop ax
	mov cl,1
	call ReadOneSector
	pop ax
	call GetFATEntry
	cmp ax,0fffh
	jz FileLoaded
	push ax
	mov dx,RootDirSectors
	add ax,dx
	add ax,SectorBalance
	add bx,[BPB_BytesPerSec]
	jmp GoOnLoadingFile
FileLoaded:
	jmp BaseOfLoader:OffsetOfLoader


RootDirSizeForLoop dw RootDirSectors
SectorNo dw 0
Odd db 0

StartBootMessage: db "start Boot"
NoLoaderMessage: db "ERROR:No LOADER IS FOUND"
LoaderFileName: db "LOADER  BIN",0

times 510-($-$$) db 0
db 0x55,0xaa
