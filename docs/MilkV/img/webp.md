#### transform to webp
```
brew install webp

cwebp ch343-usb-uart-board.png -q 85 -o ch343-usb-uart-board.webp
```
Usage:

   cwebp [options] -q quality input.png -o output.webp

where quality is between 0 (poor) to 100 (very good).
Typical value is around 80.

Try -longhelp for an exhaustive list of advanced options.

#### magick
```
brew install imagemagick

magick ch343-usb-uart-board.png \
  -alpha set \
  -fuzz 8% \
  -fill none -draw "color 1,1 floodfill" \
  -trim +repage \
  ch343-usb-uart-board.webp
```
