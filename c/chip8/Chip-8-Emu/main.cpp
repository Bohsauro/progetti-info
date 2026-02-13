#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <array>
#include <cstdint>
#include <cstdlib>

void print(int screen[64][32], float size, sf::RenderWindow& window) {
    std::vector<sf::RectangleShape> tiles;

    window.clear(sf::Color::Black);


    for (int x = 0; x < 64; x++)
    {
        for (int y = 0; y < 32; y++)
        {
            if (screen[x][y] == 1)
            {
                sf::RectangleShape tile(sf::Vector2f(size, size));
                tile.setPosition({x * size, y * size});
                tile.setFillColor(sf::Color::Green);

                tiles.push_back(tile);
            }
        }
    }

    for (int i = 0; i < tiles.size(); i++) {
        window.draw(tiles[i]);
    }
    window.display();
}

void push(std::array<uint16_t, 16>& stack, uint8_t& sp, uint16_t valore) {
    if (sp < 16) {          // Controllo Stack Overflow
        stack[sp] = valore;
        sp++;               // Sposta il puntatore al prossimo slot libero
    }
}

void pop(const std::array<uint16_t, 16>& stack, uint8_t& sp) {
    if (sp > 0) {           // Controllo Stack Underflow
        sp--;               // Torna all'ultimo elemento occupato
    }
}

void decode(uint16_t opcode, int screen[64][32], sf::RenderWindow& window, uint16_t& pc, std::array<uint16_t, 16>& stack, uint8_t& sp, std::array<uint8_t, 16>& V, uint16_t& I, std::array<uint8_t, 4096> memory) {
    switch (opcode & 0xF000) {
        case 0x0000:
            if (opcode & 0x000F) {
                for (int i = 0; i < 64; i++) {
                    for (int j = 0; j < 32; j++) {
                        screen[i][j] = 0;
                    }
                }
                print(screen, 0, window);
                break;
            } else {
                pc = stack[sp];
                pop(stack, sp);
                break;
            }

        case 0x1000:
            pc = opcode & 0x0FFF;
            break;
        case 0x2000:
            push(stack, sp, pc);
            pc = opcode & 0x0FFF;
            break;
        case 0x3000:
            if (V[(opcode & 0x0F00) >> 8] == (opcode & 0x00FF)) {
                pc += 2;
            } break;
        case 0x4000:
            if (V[(opcode & 0x0F00) >> 8] != (opcode & 0x00FF)) {
                pc += 2;
            } break;
        case 0x5000:
            if (V[(opcode & 0x0F00) >> 8] == V[(opcode & 0x00F0) >> 4]) {
                pc += 2;
            } break;
        case 0x9000:
            if (V[(opcode & 0x0F00) >> 8] != V[(opcode & 0x00F0) >> 4]) {
                pc += 2;
            } break;
        case 0x6000:
            V[(opcode & 0x0F00) >> 8] = opcode & 0x000F;
            break;
        case 0x7000:
            V[(opcode & 0x0F00) >> 8] += opcode & 0x00FF;
            break;
        case 0x8000:
            switch (opcode & 0x000F) {
                case 0x0000:
                    V[(opcode & 0x0F00) >> 8] = V[(opcode & 0x00F0) >> 4];
                    break;
                case 0x0001:
                    V[(opcode & 0x0F00) >> 8] = V[(opcode & 0x0F00) >> 8] | V[(opcode & 0x00F0) >> 4];
                    break;
                case 0x0002:
                    V[(opcode & 0x0F00) >> 8] = V[(opcode & 0x0F00) >> 8] & V[(opcode & 0x00F0) >> 4];
                    break;
                case 0x0003:
                        V[(opcode & 0x0F00) >> 8] = V[(opcode & 0x0F00) >> 8] ^ V[(opcode & 0x00F0) >> 4];
                        break;
                case 0x0004:
                        if (V[(opcode & 0x0F00) >> 8] + V[(opcode & 0x00F0) >> 4] > 255) {
                            V[15] = 1;
                        } else {
                            V[15] = 0;
                        }
                        V[(opcode & 0x0F00) >> 8] = V[(opcode & 0x0F00) >> 8] + V[(opcode & 0x00F0) >> 4];
                        break;
                case 0x0005:
                        if (V[(opcode & 0x0F00) >> 8] > V[(opcode & 0x00F0) >> 4]) {
                            V[15] = 1;
                        } else {
                            V[15] = 0; //FORSE ERRATO
                        }
                        V[(opcode & 0x0F00) >> 8] = V[(opcode & 0x0F00) >> 8] - V[(opcode & 0x00F0) >> 4];
                        break;
                case 0x0007:
                        if (V[(opcode & 0x0F00) >> 8] > V[(opcode & 0x00F0) >> 4]) {
                            V[15] = 1;
                        } else {
                            V[15] = 0; //FORSE ERRATO
                        }
                        V[(opcode & 0x0F00) >> 8] = V[(opcode & 0x00F0) >> 4] - V[(opcode & 0x0F00) >> 8];
                        break;
                case 0x0006:
                    V[(opcode & 0x0F00) >> 8] = V[(opcode & 0x00F0) >> 4]; // CONFIGURABILE
                    V[15] = (V[(opcode & 0x0F00) >> 8] & 0x00000001);

                    V[(opcode & 0x0F00) >> 8] = V[(opcode & 0x0F00) >> 8] >> 1;
                    break;
                case 0x000E:
                    V[(opcode & 0x0F00) >> 8] = V[(opcode & 0x00F0) >> 4]; // CONFIGURABILE
                    V[15] = (V[(opcode & 0x0F00) >> 8] & 0x10000000);

                    V[(opcode & 0x0F00) >> 8] = V[(opcode & 0x0F00) >> 8] << 1;
                    break;
            }
        case 0xA000:
            I = opcode & 0x0FFF;
            break;
        case 0xB000:
            pc = (opcode & 0x0FFF) + V[0];
            break;
        case 0xC000:
            V[opcode & 0x0F00] = (rand() % 256) & (opcode & 0x00FF);
            break;
        case 0xD000:
            // Coordinate di partenza dai registri
            int x_start = V[(opcode & 0x0F00) >> 8] & 63;
            int y_start = V[(opcode & 0x00F0) >> 4] & 31;
            int height = (opcode & 0x000F);

            V[0xF] = 0; // Reset flag collisione

            for (int row = 0; row < height; row++) {
                // Se la riga corrente supera il bordo inferiore (32), interrompi il disegno
                if (y_start + row >= 32) break;

                // Prendi il byte dello sprite dalla memoria RAM
                uint8_t spriteByte = memory[I + row];

                for (int col = 0; col < 8; col++) {
                    // Se la colonna corrente supera il bordo destro (64), interrompi questa riga
                    if (x_start + col >= 64) break;

                    // Isola il bit dello sprite (dal più significativo al meno significativo)
                    uint8_t spritePixel = (spriteByte >> (7 - col)) & 0x1;

                    if (spritePixel == 1) {
                        // Se il pixel sullo schermo è già 1, abbiamo una collisione (VF = 1)
                        if (screen[x_start + col][y_start + row] == 1) {
                            V[0xF] = 1;
                        }

                        // XOR del pixel: 0 diventa 1, 1 diventa 0 (spegnimento)
                        screen[x_start + col][y_start + row] ^= 1;
                    }
                }
            }
            break;

        case 0xE000:
            break; //key.















    }
}

int main() {
    int screen[64][32] = {0};
    float width = 64;
    float height = 32;
    float size = 10;

    constexpr std::array<uint8_t, 80> chip8_fontset =
    {
        0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
        0x20, 0x60, 0x20, 0x20, 0x70, // 1
        0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
        0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
        0x90, 0x90, 0xF0, 0x10, 0x10, // 4
        0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
        0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
        0xF0, 0x10, 0x20, 0x40, 0x40, // 7
        0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
        0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
        0xF0, 0x90, 0xF0, 0x90, 0x90, // A
        0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
        0xF0, 0x80, 0x80, 0x80, 0xF0, // C
        0xE0, 0x90, 0x90, 0x90, 0xE0, // D
        0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
        0xF0, 0x80, 0xF0, 0x80, 0x80  // F
    };


    // MEMORY
    std::array<uint8_t, 4096> memory{};

    for (size_t i = 0; i < chip8_fontset.size(); i++)
    {
        memory[0x050 + i] = chip8_fontset[i]; // font
    }

    // REGISTERS V0 - VF
    std::array<uint8_t, 16> V{};

    // INDEX REGISTER (16 bit)
    uint16_t I = 0;

    // PROGRAM COUNTER
    uint16_t pc = 0x200; // i programmi partono da 0x200

    // STACK (16 livelli)
    std::array<uint16_t, 16> stack{};
    uint8_t sp = 0; // stack pointer

    // TIMERS
    uint8_t delayTimer = 0;
    uint8_t soundTimer = 0;




    sf::RenderWindow window(
        sf::VideoMode({static_cast<unsigned>(width*size), static_cast<unsigned>(height*size)}),
        "Chip-8-EMULATOR",
        sf::Style::Titlebar | sf::Style::Close
    );
    window.setFramerateLimit(60);

    while (window.isOpen()) {
        while (const auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        for (int i = 0; i < 11; i++) {
            //FETCH
            uint16_t opcode = memory[pc] << 8 | memory[pc + 1];
            decode(opcode);
            pc += 2;

        }

        //update timer
        if (delayTimer > 0) {
            delayTimer--;
        }
        if (soundTimer > 0) {
            soundTimer--;
        }


    }
}
