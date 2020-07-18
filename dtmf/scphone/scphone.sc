/**
* DTMF generator!
*
* TODO: 
*
*/


(
Server.default.options.device = "Soundflower (64ch)";

Server.default.waitForBoot({

    var telephoneArray = [[1336,941],[1209,697],[1336,697],[1477,697],[1209,770],[1336,770],[1477,770],[1209,852],[1336,852],[1477,852]]; //make into Scale

    SynthDef.new(\sine, {
        arg freq = [1336,941], duration = 0.25;
        var sig = (EnvGen.kr(Env.linen(0.001,duration,0.001))*SinOsc.ar(freq, mul: 0.5));
        Out.ar(0, Mix(sig)!2)
    }).add;

    Server.default.sync;

    Pbind.new(
        \instrument, \sine,
        \freq, Pfuncn.new({
            var index = Array.fill(10, {arg i; i}).choose;
            index.postln;
            telephoneArray[index];
        },  repeats: inf),
        \dur, Prand([0.5,0.75, 1/3], repeats: inf )
    ).play;

});
)
