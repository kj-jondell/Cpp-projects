/**
* DTMF generator!
*
* TODO: 
*
*/


(
Server.default.options.device = "Soundflower (64ch)";

Server.default.waitForBoot({

    var window; //GUI elements
    var size = 50, rows = 3, margin = 10, buttons = 12;
    var symbols = ["1", "2", "3","4","5","6","7","8","9", "*", "0", "#"];

    var telephoneArray = [[1209,697],[1336,697],[1477,697],[1209,770],[1336,770],[1477,770],[1209,852],[1336,852],[1477,852], [1209, 941], [1336,941], [1477, 941]]; //make into Scale

    SynthDef.new(\sine, {
        arg freq = [1336,941], duration = 0.25;
        var sig = (EnvGen.kr(Env.linen(0.001,duration,0.001))*SinOsc.ar(freq, mul: 0.5));
        Out.ar(0, Mix(sig)!2)
    }).add;

    Server.default.sync;

    // Pbind.new(
    //     \instrument, \sine,
    //     \freq, Pfuncn.new({
    //         var index = Array.fill(10, {arg i; i}).choose;
    //         index.postln;
    //         telephoneArray[index];
    //     },  repeats: inf),
    //     \dur, Prand([0.5,0.75, 1/3], repeats: inf )
    // ).play;

    window = Window.new("Phone", Rect(200,200,(size*rows)+(margin*2),(size*(buttons/rows))+(margin*2)));

    buttons.do({
        arg index;
        Button(window, Rect(margin+(size*(index%3)), margin+(size*(index/3).asInteger), size, size)).states_([[symbols[index]]]).action_({Synth.new(\sine, [\freq, telephoneArray[index]]); telephoneArray[index].postln;});
    });

    window.front;
});
)
