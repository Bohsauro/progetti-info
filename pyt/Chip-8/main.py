#chip 8
import pygame
import numpy as np
import random

width = 64
height = 32
pixel_state = [[0 for _ in range(width)] for _ in range(height)]

size = 10
KEYMAP = {
    pygame.K_1: 0x1,
    pygame.K_2: 0x2,
    pygame.K_3: 0x3,
    pygame.K_4: 0xC,

    pygame.K_q: 0x4,
    pygame.K_w: 0x5,
    pygame.K_e: 0x6,
    pygame.K_r: 0xD,

    pygame.K_a: 0x7,
    pygame.K_s: 0x8,
    pygame.K_d: 0x9,
    pygame.K_f: 0xE,

    pygame.K_z: 0xA,
    pygame.K_x: 0x0,
    pygame.K_c: 0xB,
    pygame.K_v: 0xF,
}
FONT_SET = [
    0xF0, 0x90, 0x90, 0x90, 0xF0,  # 0
    0x20, 0x60, 0x20, 0x20, 0x70,  # 1
    0xF0, 0x10, 0xF0, 0x80, 0xF0,  # 2
    0xF0, 0x10, 0xF0, 0x10, 0xF0,  # 3
    0x90, 0x90, 0xF0, 0x10, 0x10,  # 4
    0xF0, 0x80, 0xF0, 0x10, 0xF0,  # 5
    0xF0, 0x80, 0xF0, 0x90, 0xF0,  # 6
    0xF0, 0x10, 0x20, 0x40, 0x40,  # 7
    0xF0, 0x90, 0xF0, 0x90, 0xF0,  # 8
    0xF0, 0x90, 0xF0, 0x10, 0xF0,  # 9
    0xF0, 0x90, 0xF0, 0x90, 0x90,  # A
    0xE0, 0x90, 0xE0, 0x90, 0xE0,  # B
    0xF0, 0x80, 0x80, 0x80, 0xF0,  # C
    0xE0, 0x90, 0x90, 0x90, 0xE0,  # D
    0xF0, 0x80, 0xF0, 0x80, 0xF0,  # E
    0xF0, 0x80, 0xF0, 0x80, 0x80   # F
]


# Memoria da 4KB (8-bit per locazione)
memory = np.zeros(4096, dtype=np.uint8)
FONT_START = 0x050

for i, byte in enumerate(FONT_SET):
    memory[FONT_START + i] = byte

#CARICO ROM
with open("5-quirks.ch8", "rb") as f:
    rom_data = f.read()  # rom_data è un oggetto bytes

start_address = 0x200
memory[start_address:start_address + len(rom_data)] = np.frombuffer(rom_data, dtype=np.uint8)




# 16 Registri generali V0-VF (8-bit)
V = np.zeros(16, dtype=np.uint8)

# Registro I e Program Counter (16-bit)
I = np.uint16(0)
pc = np.uint16(0x200) # Il CHIP-8 parte solitamente da 0x200

stack = []

#timer da implementare
delay_timer = 0
sound_timer = 0

def update_timers():
    global delay_timer, sound_timer

    if delay_timer > 0:
        delay_timer -= 1

    if sound_timer > 0:
        sound_timer -= 1
        if sound_timer == 0:
            pass
            #stop_beep()  # opzionale

def fetch_opcode(memory, pc):
    opcode = (np.uint16(memory[pc]) << 8) | np.uint16(memory[pc + 1])
    pc += 2
    return opcode, pc


def decode_execute(opcode):
    global pc, I, V, memory
    global pixel_state
    global draw_flag
    global stack
    global keypad
    global delay_timer, sound_timer
    # Configurabile: True = vecchio COSMAC VIP, False = moderno CHIP-48
    shift_vy = True
    match opcode & 0xF000:
        case 0x0000:
            if opcode == 0x00E0: #clear screen
                screen.fill("black")
                pixel_state = [[0 for _ in range(width)] for _ in range(height)]
                draw_flag = True
            if opcode == 0x00EE:
                pc = stack.pop()

        case 0x1000:
            pc = opcode & 0x0FFF # jump
        
        case 0x2000:
            stack.append(pc)
            pc = opcode & 0x0FFF
        
        case 0x3000: #skip se vx = nn
            if V[(opcode & 0x0F00) >> 8] == (opcode & 0x00FF):
                pc += 2
        
        case 0x4000: #skip se vx != nn
            if V[(opcode & 0x0F00) >> 8] != (opcode & 0x00FF):
                pc += 2

        case 0x5000: #skip se vx == vy
            if V[(opcode & 0x0F00) >> 8] == V[(opcode & 0x00F0) >> 4]:
                pc += 2

        case 0x9000: #skip se vx != vy
            if V[(opcode & 0x0F00) >> 8] != V[(opcode & 0x00F0) >> 4]:
                pc += 2

        case 0x6000: #set
            V[(opcode & 0x0F00) >> 8] = (opcode & 0x00FF)
        case 0x7000: #add
            V[(opcode & 0x0F00) >> 8] = (V[(opcode & 0x0F00) >> 8] + (opcode & 0x00FF)) & 0xFF

        case 0xA000: #set index
            I = (opcode & 0x0FFF)
        
        case 0xD000: #display
           
            print(np.sum(pixel_state))  # deve essere >0 se ci sono pixel accesi

            draw_flag = True
            x0 = V[(opcode & 0x0F00) >> 8] & 63
            y0 = V[(opcode & 0x00F0) >> 4] & 31
            n  = opcode & 0x000F

            V[0xF] = 0  # VF = collision flag

            y = y0
            for riga in range(n):
                if y >= 32:
                    break

                sprite_byte = memory[I + riga]
                x = x0

                for bit_index in range(8):
                    if x >= 64:
                        break

                    sprite_bit = (sprite_byte >> (7 - bit_index)) & 1

                    if sprite_bit == 1:
                        if pixel_state[y][x] == 1:
                            pixel_state[y][x] = 0
                            V[0xF] = 1
                        else:
                            pixel_state[y][x] = 1

                    x += 1

                y += 1

        case 0x8000:  # logica e aritmetica
            x = (opcode & 0x0F00) >> 8
            y = (opcode & 0x00F0) >> 4

            match opcode & 0x000F:

                # 8XY0 - Vx = Vy
                case 0x0000:
                    V[x] = V[y]

                # 8XY1 - Vx |= Vy
                case 0x0001:
                    V[x] |= V[y]

                # 8XY2 - Vx &= Vy
                case 0x0002:
                    V[x] &= V[y]

                # 8XY3 - Vx ^= Vy
                case 0x0003:
                    V[x] ^= V[y]

                # 8XY4 - Vx += Vy, VF = carry
                case 0x0004:
                    result = V[x] + V[y]
                    V[0xF] = 1 if result > 0xFF else 0
                    V[x] = result & 0xFF

                # 8XY5 - Vx -= Vy, VF = NOT borrow
                case 0x0005:
                    V[0xF] = 1 if V[x] >= V[y] else 0
                    V[x] = (V[x] - V[y]) & 0xFF

                # 8XY6 - Vx >>= 1, VF = LSB
                case 0x0006:
                    V[0xF] = V[x] & 0x01
                    V[x] >>= 1

                # 8XY7 - Vx = Vy - Vx, VF = NOT borrow
                case 0x0007:
                    V[0xF] = 1 if V[y] >= V[x] else 0
                    V[x] = (V[y] - V[x]) & 0xFF

                # 8XYE - Vx <<= 1, VF = MSB
                case 0x000E:
                    V[0xF] = (V[x] & 0x80) >> 7
                    V[x] = (V[x] << 1) & 0xFF


        case 0xB000:
            pc = (opcode & 0x0FFF) + V[0]

        case 0xC000:
            V[(opcode & 0x0F00 ) >> 8] = random.randint(0, 255) & (opcode &0x00FF)
        case 0xE000:
            key =  (opcode & 0x0F00) >> 16
            if(opcode & 0x00F0) == 0x0090:
                if keypad[key]:
                    pc += 2
            if(opcode & 0x00F0) == 0x00A0:
                if not keypad[key]:
                    pc += 2
        case 0xF000:
            x = (opcode & 0x0F00) >> 8

            match opcode & 0x000F:
                # FX07 - Vx = delay_timer
                case 0x0007:
                    V[x] = delay_timer

                # FX15, FX55, FX65
                case 0x0005:
                    match opcode & 0x00F0:
                        # FX15 - delay_timer = Vx
                        case 0x0010:
                            delay_timer = V[x]

                        # FX55 - store V0..Vx in memory starting at I
                        case 0x0050:
                            for k in range(x + 1):
                                memory[I + k] = V[k]

                        # FX65 - load V0..Vx from memory starting at I
                        case 0x0060:
                            for k in range(x + 1):
                                V[k] = memory[I + k]

                # FX18 - sound_timer = Vx
                case 0x0008:
                    sound_timer = V[x]

                # FX1E - I += Vx
                case 0x000E:
                    I += V[x]

                # FX0A - wait for key press
                case 0x000A:
                    key_pressed = False
                    for i, k in enumerate(keypad):
                        if k:
                            V[x] = i
                            key_pressed = True
                            break

                    if not key_pressed:
                        pc -= 2  # ripeti l'istruzione

                # FX29 - I = location of sprite for digit Vx
                case 0x0009:
                    I = FONT_START + 5 * V[x]

                # FX33 - BCD of Vx
                case 0x0003:
                    n = V[x]
                    memory[I]     = n // 100
                    memory[I + 1] = (n // 10) % 10
                    memory[I + 2] = n % 10


                
        
        
        case default:
            print("comando non trovato")






            






def draw_screen():
    global pixel_state
    screen.fill((0, 0, 0))  # pulisci lo sfondo
    for y in range(height):
        for x in range(width):
            if pixel_state[y][x]:
                rect = pygame.Rect(x*size, y*size, size, size)  # attenzione a pygame.Rect e virgole
                pygame.draw.rect(screen, (255, 255, 255), rect)
            else:
                rect = pygame.Rect(x*size, y*size, size, size)  # attenzione a pygame.Rect e virgole
                pygame.draw.rect(screen, (0, 0, 0), rect)
    pygame.display.flip()  # aggiorna lo schermo




CPU_CYCLES_PER_FRAME = 10

pygame.init()
screen = pygame.display.set_mode((width*size, height*size))
clock = pygame.time.Clock()
running = True

screen.fill("black")
draw_flag = False

keypad = [0] * 16


while running:
    # poll for events
    # pygame.QUIT event means the user clicked X to close your window
    for event in pygame.event.get():
        for event in pygame.event.get():
            if event.type == pygame.KEYDOWN:
                if event.key in KEYMAP:
                    chip8_key = KEYMAP[event.key]
                    keypad[chip8_key] = 1   # tasto premuto
                elif event.type == pygame.KEYUP:
                    if event.key in KEYMAP:
                        chip8_key = KEYMAP[event.key]
                        keypad[chip8_key] = 0   # tasto rilasciato

            

        if event.type == pygame.QUIT:
            running = False
    
    # fill the screen with a color to wipe away anything from last frame
    for _ in range(CPU_CYCLES_PER_FRAME):
        opcode, pc = fetch_opcode(memory, pc)
        decode_execute(opcode)   # <-- QUI lo switch

    # timer (60 Hz)
    update_timers()


    # RENDER YOUR GAME HERE

    if draw_flag:
        draw_screen()
        draw_flag = False


    clock.tick(60)  # limits FPS to 60

pygame.quit()