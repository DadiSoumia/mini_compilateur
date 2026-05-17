; ============================================
; Code Assembleur 8086 genere automatiquement
; ============================================

PILE SEGMENT STACK
    DW 100 DUP(?)
base_pile EQU $
PILE ENDS

DONNEE SEGMENT
    x DW ?
    y DW ?
    z DW ?
    a DW ?
    b DW ?
    somme DW ?
    i DW ?
    j DW ?
    moyenne DW ?
    T0 DW ?
    T1 DW ?
    T2 DW ?
    T3 DW ?
    T4 DW ?
    T5 DW ?
    T6 DW ?
    T7 DW ?
    T8 DW ?
    T9 DW ?
    T10 DW ?
    T11 DW ?
    T12 DW ?
    T14 DW ?
    T15 DW ?
    T16 DW ?
    T17 DW ?
    T18 DW ?
    T19 DW ?
    T20 DW ?
    T21 DW ?
    T22 DW ?
    T23 DW ?
    T24 DW ?
    T25 DW ?
    T26 DW ?
    T27 DW ?
    T28 DW ?
    T29 DW ?
    T30 DW ?
    T31 DW ?
    T33 DW ?
    T34 DW ?
    T35 DW ?
    T36 DW ?
    T38 DW ?
    T39 DW ?
    T40 DW ?
    T41 DW ?
    T42 DW ?
DONNEE ENDS

LECODE SEGMENT
Debut:
    ASSUME CS:LECODE, DS:DONNEE, SS:PILE
    ; Initialisation des segments
    MOV AX, DONNEE
    MOV DS, AX
    MOV AX, PILE
    MOV SS, AX
    MOV SP, base_pile

L0:
    MOV AX, 10
    MOV x, AX

L1:
    MOV AX, 5
    MOV y, AX

L2:
    MOV AX, 2
    MOV z, AX

L3:
    MOV AX, 2.5
    MOV a, AX

L4:
    MOV AX, a
    MOV BX, Pi
    ADD AX, BX
    MOV T0, AX

L5:
    MOV AX, T0
    MOV BX, 2.0
    IMUL BX
    MOV T1, AX

L6:
    MOV AX, T1
    MOV b, AX

L7:
    MOV AX, y
    MOV BX, z
    IMUL BX
    MOV T2, AX

L8:
    MOV AX, x
    MOV BX, T2
    ADD AX, BX
    MOV T3, AX

L9:
    MOV AX, T3
    MOV Tabint[0], AX

L10:
    MOV AX, b
    MOV BX, 3.5
    ADD AX, BX
    MOV T4, AX

L11:
    MOV AX, T4
    CWD
    MOV BX, 2.0
    IDIV BX
    MOV T5, AX

L12:
    MOV AX, T5
    MOV Tabfloat[1], AX

L13:
    MOV AX, x
    MOV BX, y
    SUB AX, BX
    MOV T6, AX

L14:
    MOV AX, 17
    CMP AX, 0
    JG L17

L15:
    MOV AX, 0
    MOV T6, AX

L16:
    JMP L18

L17:
    MOV AX, 1
    MOV T6, AX

L18:
    MOV AX, x
    MOV BX, y
    ADD AX, BX
    MOV T7, AX

L19:
    MOV AX, z
    MOV BX, T7
    SUB AX, BX
    MOV T8, AX

L20:
    MOV AX, 23
    CMP AX, 0
    JL L23

L21:
    MOV AX, 0
    MOV T8, AX

L22:
    JMP L24

L23:
    MOV AX, 1
    MOV T8, AX

L24:
    MOV AX, T6
    CMP AX, 0
    JE L28

L25:
    MOV AX, T8
    CMP AX, 0
    JE L28

L26:
    MOV AX, 1
    MOV T9, AX

L27:
    JMP L29

L28:
    MOV AX, 0
    MOV T9, AX

L29:
    MOV AX, y
    SUB AX, 0
    MOV T10, AX

L30:
    MOV AX, T10
    CMP AX, 0
    JE L33

L31:
    MOV AX, 0
    MOV T10, AX

L32:
    JMP L34

L33:
    MOV AX, 1
    MOV T10, AX

L34:
    MOV AX, T10
    CMP AX, 0
    JE L37

L35:
    MOV AX, 0
    MOV T11, AX

L36:
    JMP L38

L37:
    MOV AX, 1
    MOV T11, AX

L38:
    MOV AX, T9
    CMP AX, 0
    JNE L42

L39:
    MOV AX, T11
    CMP AX, 0
    JNE L42

L40:
    MOV AX, 0
    MOV T12, AX

L41:
    JMP L43

L42:
    MOV AX, 1
    MOV T12, AX

L43:
    MOV AX, T12
    CMP AX, 0
    JE L81

L45:
    MOV AX, T7
    MOV BX, z
    ADD AX, BX
    MOV T14, AX

L46:
    MOV AX, T14
    MOV somme, AX

L47:
    MOV AX, 0
    MOV i, AX

L48:
    MOV AX, i
    SUB AX, 10
    MOV T15, AX

L49:
    MOV AX, 52
    CMP AX, 0
    JLE L52

L50:
    MOV AX, 0
    MOV T15, AX

L51:
    JMP L53

L52:
    MOV AX, 1
    MOV T15, AX

L53:
    MOV AX, T15
    CMP AX, 0
    JE L80

L54:
    MOV AX, Tabint[i]
    MOV BX, i
    ADD AX, BX
    MOV T16, AX

L55:
    MOV AX, T16
    MOV Tabint[i], AX

L56:
    MOV AX, i
    SUB AX, 5
    MOV T17, AX

L57:
    MOV AX, 60
    CMP AX, 0
    JL L60

L58:
    MOV AX, 0
    MOV T17, AX

L59:
    JMP L61

L60:
    MOV AX, 1
    MOV T17, AX

L61:
    MOV AX, Tabint[i]
    SUB AX, 10
    MOV T18, AX

L62:
    MOV AX, 65
    CMP AX, 0
    JG L65

L63:
    MOV AX, 0
    MOV T18, AX

L64:
    JMP L66

L65:
    MOV AX, 1
    MOV T18, AX

L66:
    MOV AX, T17
    CMP AX, 0
    JE L70

L67:
    MOV AX, T18
    CMP AX, 0
    JE L70

L68:
    MOV AX, 1
    MOV T19, AX

L69:
    JMP L71

L70:
    MOV AX, 0
    MOV T19, AX

L71:
    MOV AX, T19
    CMP AX, 0
    JE L75

L72:
    MOV AX, Tabint[i]
    MOV BX, 1.5
    IMUL BX
    MOV T20, AX

L73:
    MOV AX, T20
    MOV Tabfloat[i], AX

L74:
    JMP L77

L75:
    MOV AX, Tabint[i]
    CWD
    MOV BX, 2.0
    IDIV BX
    MOV T21, AX

L76:
    MOV AX, T21
    MOV Tabfloat[i], AX

L77:
    MOV AX, i
    ADD AX, 1
    MOV T22, AX

L78:
    MOV AX, T22
    MOV i, AX

L79:
    JMP L48

L80:
    JMP L82

L81:
    MOV AX, 0
    MOV somme, AX

L82:
    MOV AX, x
    MOV BX, Max
    SUB AX, BX
    MOV T23, AX

L83:
    MOV AX, 86
    CMP AX, 0
    JLE L86

L84:
    MOV AX, 0
    MOV T23, AX

L85:
    JMP L87

L86:
    MOV AX, 1
    MOV T23, AX

L87:
    MOV AX, T10
    MOV T24, AX

L88:
    MOV AX, T10
    CMP AX, 0
    JNE L91

L89:
    MOV AX, 0
    MOV T24, AX

L90:
    JMP L92

L91:
    MOV AX, 1
    MOV T24, AX

L92:
    MOV AX, z
    SUB AX, 10
    MOV T25, AX

L93:
    MOV AX, 96
    CMP AX, 0
    JL L96

L94:
    MOV AX, 0
    MOV T25, AX

L95:
    JMP L97

L96:
    MOV AX, 1
    MOV T25, AX

L97:
    MOV AX, T24
    CMP AX, 0
    JNE L101

L98:
    MOV AX, T25
    CMP AX, 0
    JNE L101

L99:
    MOV AX, 0
    MOV T26, AX

L100:
    JMP L102

L101:
    MOV AX, 1
    MOV T26, AX

L102:
    MOV AX, T23
    CMP AX, 0
    JE L106

L103:
    MOV AX, T26
    CMP AX, 0
    JE L106

L104:
    MOV AX, 1
    MOV T27, AX

L105:
    JMP L107

L106:
    MOV AX, 0
    MOV T27, AX

L107:
    MOV AX, T27
    CMP AX, 0
    JE L129

L108:
    MOV AX, x
    ADD AX, 1
    MOV T28, AX

L109:
    MOV AX, T28
    MOV x, AX

L110:
    MOV AX, x
    MOV BX, y
    SUB AX, BX
    MOV T29, AX

L111:
    MOV AX, T29
    CMP AX, 0
    JE L114

L112:
    MOV AX, 0
    MOV T29, AX

L113:
    JMP L115

L114:
    MOV AX, 1
    MOV T29, AX

L115:
    MOV AX, T29
    CMP AX, 0
    JE L118

L116:
    MOV AX, 0
    MOV T30, AX

L117:
    JMP L119

L118:
    MOV AX, 1
    MOV T30, AX

L119:
    MOV AX, T30
    CMP AX, 0
    JE L128

L120:
    MOV AX, y
    ADD AX, 1
    MOV T31, AX

L121:
    MOV AX, T31
    MOV y, AX

L123:
    MOV AX, Tabint[0]
    MOV BX, Tabint[1]
    ADD AX, BX
    MOV T33, AX

L124:
    MOV AX, x
    MOV BX, y
    SUB AX, BX
    MOV T34, AX

L125:
    MOV AX, T33
    MOV BX, T34
    IMUL BX
    MOV T35, AX

L126:
    MOV AX, T35
    MOV Tabint[T32], AX

L127:
    JMP L119

L128:
    JMP L107

L129:
    MOV AX, 1
    MOV j, AX

L130:
    MOV AX, j
    SUB AX, 20
    MOV T36, AX

L131:
    MOV AX, 134
    CMP AX, 0
    JLE L134

L132:
    MOV AX, 0
    MOV T36, AX

L133:
    JMP L135

L134:
    MOV AX, 1
    MOV T36, AX

L135:
    MOV AX, T36
    CMP AX, 0
    JE L145

L137:
    MOV AX, Tabfloat[T37]
    MOV BX, Tabfloat[j]
    ADD AX, BX
    MOV T38, AX

L138:
    MOV AX, T38
    CWD
    MOV BX, 2.0
    IDIV BX
    MOV T39, AX

L139:
    MOV AX, T39
    MOV Tabfloat[j], AX

L140:
    MOV AX, moyenne
    MOV BX, Tabfloat[j]
    ADD AX, BX
    MOV T40, AX

L141:
    MOV AX, T40
    MOV moyenne, AX

L142:
    MOV AX, j
    ADD AX, 1
    MOV T41, AX

L143:
    MOV AX, T41
    MOV j, AX

L144:
    JMP L130

L145:
    MOV AX, moyenne
    CWD
    MOV BX, 20.0
    IDIV BX
    MOV T42, AX

L146:
    MOV AX, T42
    MOV moyenne, AX

L147:
    ; INPUT: lire valeur dans x
    ; (lire depuis stdin dans AX)
    MOV x, AX

L148:
    ; OUTPUT: "Valeur finale de x: "  valeur=x
    MOV AX, x
    ; (afficher AX)

L149:
    ; OUTPUT: "Somme: "  valeur=somme
    MOV AX, somme
    ; (afficher AX)

L150:
    ; OUTPUT: "Moyenne: "  valeur=moyenne
    MOV AX, moyenne
    ; (afficher AX)

L151:
    ; Fin du programme
    MOV AH, 4Ch
    INT 21h

LECODE ENDS

END Debut
