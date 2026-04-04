# Dokumentasi Earthquake Simulator (quake_sim)

Proyek ini adalah simulator pergerakan lempeng tektonik yang mengakibatkan gempa bumi. Program ini menggunakan bahasa pemrograman C dengan library grafis **Raylib** dan menerapkan arsitektur **MVC (Model-View-Controller)** agar kode terorganisir dengan baik. Proyek ini berfokus pada visualisasi gempa tektonik dengan gaya ilustratif.

## Arsitektur Proyek (MVC)

Simulator ini dibagi menjadi tiga bagian utama:
1.  **Model**: Tempat menyimpan data dan status aplikasi (apa yang sedang terjadi).
2.  **View**: Bagian yang menangani tampilan visual di layar (bagaimana data ditampilkan).
3.  **Controller**: Bagian yang mengontrol logika aplikasi dan input pengguna (bagaimana data berubah).

---

## Daftar File dan Penjelasannya

### 1. Root Directory
- **`main.c`**: Titik masuk utama program. File ini menginisialisasi jendela Raylib, menjalankan *main loop*, dan memanggil fungsi `Update` serta `Draw` dari Controller.
- **`Makefile.win`**: Script untuk melakukan kompilasi (build) program di Windows menggunakan GCC/MinGW.

### 2. Folder `core/` (Utilitas Dasar)
- **`framebuffer.h`**: Mendefinisikan fungsi `FB_SetPixel` untuk menggambar piksel ke layar dengan pengecekan batas agar program tidak *crash*.
- **`color_utils.c/h`**: Fungsi pembantu untuk memanipulasi warna (misal: mengatur kecerahan warna).
- **`math_utils.c/h`**: Fungsi pembantu matematika seperti interpolasi linear (Lerp) untuk animasi halus.

### 3. Folder `algo/` (Algoritma Grafis Dasar)
Folder ini berisi implementasi manual algoritma komputer grafik klasik:
- **`bresenham.c/h`**: Algoritma Bresenham untuk menggambar garis lurus, garis tebal, dan garis putus-putus secara efisien.
- **`dda.c/h`**: Algoritma DDA (*Digital Differential Analyzer*) sebagai alternatif penggambaran garis.
- **`midcircle.c/h`**: Algoritma *Midpoint Circle* untuk menggambar lingkaran yang halus.
- **`midellipse.c/h`**: Algoritma *Midpoint Ellipse* untuk menggambar bentuk elips.
- **`polygon_fill.c/h`**: Algoritma untuk mewarnai bagian dalam poligon (digunakan untuk menggambar lapisan bumi).

### 4. Folder `transform/` (Transformasi 2D)
- **`matrix3x3.c/h`**: Implementasi operasi matriks 3x3 untuk transformasi koordinat.
- **`transforms.c/h`**: Fungsi untuk melakukan Translasi (perpindahan), Rotasi (perputaran), dan Scaling (perubahan ukuran) pada objek 2D.

### 5. Folder `model/` (Data & Status)
- **`app_state.h`**: Menyimpan status global aplikasi, seperti layar mana yang sedang aktif (`MENU`, `SIMULASI`, `ABOUT`).
- **`earth_layers.c/h`**: Mendefinisikan struktur lapisan bumi (Kerak, Mantel, Inti) serta ketebalan dan warnanya.
- **`particle_model.c/h`**: Sistem partikel untuk efek visual seperti debu atau reruntuhan saat gempa terjadi.
- **`earthquake_model.c/h`**: Data utama untuk simulasi gempa bumi tektonik (perpindahan lempeng, guncangan, dan kerusakan).

### 6. Folder `view/` (Tampilan Visual)
- **`menu_view.c/h`**: Menggambar antarmuka menu utama.
- **`hud_view.c/h`**: Menggambar *Heads-Up Display* (teks informasi/instruksi di layar saat simulasi).
- **`scene_view.c/h`**: Logika dasar penggambaran latar belakang atau elemen umum di setiap *scene*.
- **`earthquake_view.c/h`**: Visualisasi utama untuk simulasi gempa bumi tektonik.

### 7. Folder `controller/` (Logika & Input)
- **`app_controller.c/h`**: Pengontrol pusat yang menghubungkan semua komponen. Ia mendeteksi input keyboard/mouse dan menentukan apa yang harus di-update atau digambar.
- **`menu_controller.c/h`**: Menangani logika navigasi di menu utama.
- **`sim_controller.c/h`**: Menangani logika jalannya simulasi (kapan lempeng bergerak, kapan gempa dipicu).

---

## Cara Kompilasi dan Menjalankan

1.  Pastikan Anda memiliki **GCC (MinGW)** dan **Raylib** terinstal di `C:/raylib`.
2.  Buka terminal/PowerShell di folder proyek.
3.  Jalankan perintah:
    ```bash
    mingw32-make -f Makefile.win
    ```
4.  Setelah selesai, jalankan file `quake_sim.exe`.
