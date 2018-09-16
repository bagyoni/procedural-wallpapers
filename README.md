# procedural-wallpapers
A collection of wallpaper generators

## How to use (Linux only)
1. `sudo apt-get install gcc imagemagick`
1. `git clone https://github.com/ba-sz-at/procedural-wallpapers.git`
1. `cd procedural-wallpapers/src`
1. Open lib/main.h for editing.
1. Change WID and HEI to the width and height of your screen (pixels), and save.
1. `./wp-gen`
1. The previous command should have generated a *wallpaper.jpg* in src/out. Set it as your desktop background.
1. Add the *wp-gen* script to your startup applications. This will change your wallpaper at each startup.

## Generators

<table width="100%">
<tr>
	<td width="50%">
		<img src="examples/clouds.jpg">
		<b>Clouds</b>
		<p>Perlin noise fed into a sigmoid function.
	</td>
	<td width="50%">
		<img src="examples/fern.jpg">
		<b>Fern</b>
		<p>Barnsley fern with mutation.
	</td>
</tr>
<tr>
	<td width="50%">
		<img src="examples/flow.jpg">
		<b>Flow</b>
		<p>Perlin flow field.
	</td>
	<td width="50%">
		<img src="examples/islands.jpg">
		<b>Islands</b>
		<p>Perlin noise fed into a cutoff function.
	</td>
</tr>
<tr>
	<td width="50%">
		<img src="examples/landscape.jpg">
		<b>Landscape</b> (<a href="https://tyrellrummage.github.io/landscape/">original source</a>)
		<p>Simulated erosion using a midpoint displacement technique.
	</td>
	<td width="50%">
		<img src="examples/lightning.jpg">
		<b>Lightning</b>
		<p>Similar to a Brownian tree but faster to generate.
	</td>
	
</tr>
<tr>
	<td width="50%">
		<img src="examples/marrowlike.jpg">
		<b>Marrowlike</b> (<a href="http://pcg.wikidot.com/forum/t-79282/multiplicative-cascades-ish">original source</a>)
		<p>If a pixel is too dark, give it a random brightness. Scale to double size. Repeat.
	</td>
	<td width="50%">
		<img src="examples/mesh.jpg">
		<b>Mesh</b>
		<p>Transformations of the complex plane.
	</td>
</tr>
<tr>
	<td width="50%">
		<img src="examples/tangles.jpg">
		<b>Tangles</b>
		<p>Rec-tangles.
	</td>
	<td width="50%">
		<img src="examples/water.jpg">
		<b>Water</b>
		<p>Very simple interference pattern generator.
	</td>
</tr>
<tr>
	<td width="50%">
		<img src="examples/wood.jpg">
		<b>Wood</b>
		<p>Modular Perlin noise stretched along the x axis.
	</td>
	<td width="50%">
		<img src="examples/zebra.jpg">
		<b>Zebra</b>
		<p>The same complex function as in the Mesh program, but from a different perspective.
	</td>
</tr>
</table>

## Disclaimers
* The *landscape* generator is shamelessly stolen from here: https://tyrellrummage.github.io/landscape/
* The *marrowlike* generator follows the recursive algorithm described here: http://pcg.wikidot.com/forum/t-79282/multiplicative-cascades-ish
* The *fern* generator uses a fractal image compression method that might be patented (I couldn't find much information about it)

## Licensing
All programs, except for those listed in the Disclaimers section, are in the public domain.