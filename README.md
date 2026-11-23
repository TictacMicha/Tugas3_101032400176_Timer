# STM32F411 Bare-Metal Timer & Interrupt

Implementasi pengendalian *timer* dan *interrupt* secara *bare-metal* (manipulasi register langsung tanpa pustaka HAL/LL) pada mikrokontroler **STM32F411CCU6 (Black Pill)** menggunakan **STM32CubeIDE**.

| Keterangan | Detail |
| :--- | :--- |
| **Nama** | `Muhammad Mirza Khairano` |
| **NIM** | `101032400176` |
| **Kelas** | `TK-48-05` |

## Konfigurasi Perangkat Keras & Pinout

* **Mikrokontroler:** STM32F411CCU6
* **Input:**
  * `PA4` — Push Button eksternal ke `GND` (*Input Pull-Up*, *active-low*)
* **Output:**
  * `PA1` — LED Eksternal (Poin 2 dan Poin 3)
  * `PA5` — LED Eksternal 1 (Poin 1: `TIM2`)
  * `PA6` — LED Eksternal 2 (Poin 1: `TIM3`)
  * `PA7` — LED Eksternal 3 (Poin 1: `TIM4`)

## Ringkasan Studi Kasus & Konfigurasi Register

| Studi Kasus | File Kode | Peripheral & Pin | Nilai Register (`PSC` / `ARR`) | Perilaku Sistem |
| :--- | :--- | :--- | :--- | :--- |
| **Poin 1: Blinking Multiple LEDs** | `poin1.c` | `TIM2` (`PA5`)<br>`TIM3` (`PA6`)<br>`TIM4` (`PA7`) | `PSC = 15999`<br>`ARR = 499` (TIM2)<br>`ARR = 249` (TIM3)<br>`ARR = 99` (TIM4) | Mengedipkan 3 LED eksternal secara bersamaan dengan frekuensi berbeda: **1 Hz** (`PA5`), **2 Hz** (`PA6`), dan **5 Hz** (`PA7`). |
| **Poin 2: Debouncing Pushbutton** | `poin2.c` | `EXTI4` (`PA4`)<br>`TIM2` (50 ms)<br>LED (`PA1`) | `PSC = 15999`<br>`ARR = 49` | Membaca penekanan push button `PA4` via interupsi `EXTI4`, menahan pembacaan selama **50 ms** dengan `TIM2`, lalu menggunakan variabel `flag` untuk mengubah status LED `PA1`. |
| **Poin 3: Push to Blink** | `poin3.c` | `GPIOA` (`PA4`)<br>`TIM3` (100 ms)<br>LED (`PA1`) | `PSC = 15999`<br>`ARR = 99` | Mengedipkan LED `PA1` pada frekuensi **5 Hz** (*toggle* tiap 100 ms) selama push button `PA4` ditahan, dan langsung mematikannya saat tombol dilepas. |

## Struktur Direktori

```text
Tugas3_101032400176_Muhammad Mirza Khairano/
├── Inc/                        # Header definisi register CMSIS (stm32f4xx.h)
├── Src/
│   └── main.c                  # File sumber utama aktif pada STM32CubeIDE
├── Startup/                    # File startup assembly mikrokontroler
├── Source_Codes/               # Arsip kode sumber lengkap untuk ketiga poin
│   ├── poin1.c
│   ├── poin2.c
│   └── poin3.c
├── .cproject
└── .project
```

