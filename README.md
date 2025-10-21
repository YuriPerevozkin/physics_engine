# Физический движок
Физический движок написанный на C

## TODO
- [x] отобразить базовые геометрические фигуры (круг, треугольник, прямоуголник)
- [] добавить динамику (как изменяется движение тел)
- [] добавить коллизию

## Библиотеки:
[raylib](https://www.raylib.com/index.html) - Графика

## Стиль кода:
https://github.com/MaJerle/c-code-style

# Установка и использование

## Установка
### windows
- установите [MINGW MSYS2](https://www.msys2.org/)
```sh
pacman -S base-devel git
pacman -S mingw-w64-x86_64-raylib
git clone https://github.com/YuriPerevozkin/physics_engine.git
cd physics_engine
```

### arch linux
```sh
sudo pacman -S raylib
git clone https://github.com/YuriPerevozkin/physics_engine.git
cd physics_engine
```

### MacOS
- установка с помощью [homebrew](https://brew.sh)
```sh
brew install raylib
brew install pkg-config
git clone https://github.com/YuriPerevozkin/physics_engine.git
cd physics_engine 
```

## Компиляция
```sh
make run
```
