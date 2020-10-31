# WHAT IS THIS?
This code was used for implementing an interactive phone for the exhibition *MAMI:AMA:MÖDRAR*, 29 august 2020 – 16 january 2021, at [Botkyrka konsthall](https://botkyrkakonsthall.se/modrar/). The installation is an artwork conceptualized by the artist Sarasvati Shrestha and contains recordings and music made or curated by the artist.

<p align="center" >
<figure class = "image">
<img src="https://user-images.githubusercontent.com/30523857/97778944-1314f500-1b7b-11eb-8fb3-c6acf876e76f.jpg" width="360" height="450" />
<figcaption>
Picture from the exhibition, Botkyrka konsthall.
</figcaption>
</figure>
</p>

# HOW IS IT WORKING?
The code is running on a Raspberry Pi Zero W and connects to the phone through a cheap USB soundcard. The phone sends it's DTMF encoded tones to the Raspberry, which are decoded and responds accordingly (e.g. by playing back a soundfile).

## DTMF (Dual Tone Multi Frequency)
A dual-tone multi-frequency signaling encoder.
