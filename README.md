##Phisical Bits

The arduino block was ment to be an introduction to the phisical computing. We started doing some simple projects that showed us the potential of this little processor.
We played around with all kind of sensors, resistors, switches, LED's...

For the end of this block, we had to build an interacting object. The output of this interaction had to be a flipdot[^flipdot]. First, we had to choose a binary process for the object to show. 

In my case, my first idea was to build a indicator of whether it is safe or not to leave the house. It would be placed next to the door from the inside.
and would directly comunicate with some household items, such as the oven, lights,... Someone who leaves the house, could actually be sure that everithing is turned off only by looking at the flipdot. 

My second idea was based on the game "chinese whispers" in which a spoken message has to pass through a group of people. While it's passing through, the message changes, because of misinterprtation.
In my project, I replaced the spoken messages by rythms, the player could introduce a rythm by touching a capacitive sensor with his finger and see it been played by the flipdot. In Chinese whispers, you would need a group of people for it to work, In my project, you would still need people, but not necesarily as a group, because between each player, it could hold up with the rythm as log as you want. I had the idea of storing each rythm in an Sd card, so that maybe tey could later be compared to eachother or visualized with Processing.

I decidet to realie the second idea, as it was more original and more fun to do.
Here is the circuit:

![10](http://i.imgur.com/aYH1kDb.png)

And some photos of the process:

![10](http://i.imgur.com/BJA2bXx.jpg)
![10](http://i.imgur.com/GkKHdmk.jpg)
![10](http://i.imgur.com/rn0b2Dt.jpg)

[Here][link5] you can ses the final product in action and [here][link6] you can find the arduino code.

I hope this was a good overview of what the course covers.



[link1]: https://github.com/varusgarcia/Input-Output/blob/master/Algorythm/Algorythm.pde
[link2]: https://docs.google.com/forms/d/1PAwjxJQz2l65CJPxiWn2zA7Dtr0jKwkhc1Q2Oo37FoQ/edit
[link3]: https://varusgarcia.github.io
[link4]: https://github.com/varusgarcia/Input-Output/tree/master/Crowdsourcing
[link5]: https://vimeo.com/123615966
[link6]: https://github.com/varusgarcia/Input-Output/blob/master/Arduino/Arduino_code.ino

[^flipdot]: What is a Flipdot? Well, it is an object that allows you to flip a circular shape, that can rotate 180º. How? the shape is magnetized and underneath there are two electomagnets with contrary polarities. When you change the  polarities (we used a h-bridge for that) the "dot" flips.