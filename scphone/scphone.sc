/**
* DTMF generator!
*
* TODO: 
*
*/


(
//Server.default.quit;
Server.default.options.device = "Soundflower (64ch)";
//Server.default.options.device = "Built-in";

Server.default.waitForBoot({

    var window; //GUI elements
    var size = 50, rows = 7, margin = 10;
    var symbols = ["1", "2", "3", "4", "5", "6", "7", "8", "9", "*", "0", "#", "M1", "M2", "M3", "M4", "M5", "M6", "M7"];

    var outVar = 0;

    var sequences = [#["1", "7", "0", "6"], #["2", "3", "0", "5"], #["4", "7", "1", "3"], #["1", "9", "#", "2"], #["0", "9", "*", "7"], #["1", "3", "2", "1"]];

    var telephoneArray = [#[1209,697],#[1336,697],#[1477,697],#[1209,770],#[1336,770],#[1477,770],#[1209,852],#[1336,852],#[1477,852],#[1209, 941],#[1336,941],#[1477, 941]]; //make into Scale

    var getIndex = {
        arg symbol;
        var returnIndex = 0;
        symbols.do({
            arg value, index;
            if(value == symbol)
            {returnIndex=index;}
        });
        returnIndex;
    };

    var quickCall = {
        arg seq = #["1","7","0","6"];
        var newSequence;
        var freqArray = Array.fill(seq.size, {
            arg index;
            telephoneArray[getIndex.value(seq[index])];
        });

        newSequence = Pbind.new(
            \instrument, \sine,
            \freq, Pseq.new(freqArray,  repeats: 1),
            \duration, Pseq.new([0.1], repeats: 4),
            \dur, Pseq.new([0.125], repeats: 4),
            \outBus, outVar
        );

        newSequence;
    }; 

    SynthDef.new(\sine, {
        arg freq = 1336, duration = 0.25, outBus = 0;
        var sig = (EnvGen.kr(Env.linen(0.001,duration,0.001), doneAction: Done.freeSelf)*SinOsc.ar(freq, mul: 0.5));
        //freq.poll(50);
        Out.ar(outBus, Mix(sig)!2)
    }).add;

    //Server.default.queryAllNodes;

    Server.default.sync;

    window = Window.new("Phone", Rect(200,200,(size*rows)+(margin*2),(size*(symbols.size/rows))+(margin*2)));

    symbols.size.do({
        arg index;
        var button = Button(window, Rect(margin+(size*(index%3)), margin+(size*(index/3).asInteger), size, size)).states_([[symbols[index]]]);
        if(index < telephoneArray.size){
            button.action_({
                Synth.new(\sine, [\freq, telephoneArray[index][0], \outBus, outVar]); 
                Synth.new(\sine, [\freq, telephoneArray[index][1], \outBus, outVar]); 
                telephoneArray[index].postln;
            });
        }
        {
            button.action_({
                quickCall.value(sequences[index%telephoneArray.size]).play;
            });
        }
    });

    window.front;
});
)
