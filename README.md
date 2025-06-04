# 🎬 Video Converter (FFmpeg Batch Tool)

Tento nástroj v jazyce C++ rekurzivně prohledá zadanou složku, najde všechny `.avi` soubory a převede je do `.mkv` formátu pomocí `ffmpeg`. Po úspěšné konverzi původní soubor odstraní.

## ✅ Funkce

- Automatická rekurzivní konverze všech `.avi` souborů ve složce
- Podpora **diakritiky** (české znaky v názvech souborů a cestách)
- Zobrazení **procentuálního průběhu** konverze
- Automatické odstranění původních `.avi` souborů po převodu
- Použití **FFmpeg** s přednastavením `ultrafast` pro rychlé zpracování

## ⚙️ Požadavky

- Windows s podporou **UTF-16 konzole**
- [FFmpeg](https://ffmpeg.org/download.html) – binárky (`ffmpeg.exe`, `ffprobe.exe`) ve stejné složce jako `video_converter.exe`
- Kompilátor s podporou C++17 (např. `g++` z MinGW)

## 💻 Kompilace (např. v VS Code)

```bash
g++ -std=c++17 -o video_converter.exe video_converter.cpp
```

## 🛠️ Použití

1. Spusť `video_converter.exe`
2. Zadej cestu ke složce, např.:
   ```
   E:\Seriály\Chalupáři
   ```
3. Sleduj průběh převodu a zprávu o odstranění původního `.avi`
