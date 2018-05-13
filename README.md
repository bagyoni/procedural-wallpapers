# procedural-wallpapers
A collection of wallpaper generators

## How to use (Linux only)
1. `sudo apt-get install gcc imagemagick`
1. `git clone https://github.com/ba-sz-at/procedural-wallpapers.git`
1. `cd procedural-wallpapers/src`
1. `./wp-gen`
1. The previous command should have generated a *wallpaper.jpg* in src. Set it as your desktop background.
1. Add the *wp-gen* script to your startup applications. This will change your wallpaper at each startup.

## Generators

<table>
<tr>
	<td>
		<img src="examples/clouds.jpg" width="400">
		<b>Clouds</b>
		<p>Perlin noise run through a sigmoid function.
	</td>
	<td>
		<img src="examples/islands.jpg" width="400">
		<b>Islands</b>
		<p>Perlin noise run through a cutoff function.
	</td>
</tr>
<tr>
	<td>
		<img src="examples/landscape.jpg" width="400">
		<b>Landscape</b> (<a href="https://tyrellrummage.github.io/landscape/">original source</a>)
		<p>Simulated erosion using a midpoint displacement technique.
	</td>
	<td>
		<img src="examples/marrowlike.jpg" width="400">
		<b>Marrowlike</b> (<a href="http://pcg.wikidot.com/forum/t-79282/multiplicative-cascades-ish">original source</a>)
		<p>If a pixel is too dark, give it a random brightness. Scale to double size. Repeat.
	</td>
</tr>
<tr>
	<td>
		<img src="examples/mesh.jpg" width="400">
		<b>Mesh</b>
		<p>Transformations of the complex plane.
	</td>
	<td>
		<img src="examples/tangles.jpg" width="400">
		<b>Tangles</b>
		<p>Rec-tangles.
	</td>
</tr>
<tr>
	<td>
		<img src="examples/fern.jpg" width="400">
		<b>Fern</b>
		<p>Barnsley-fern with mutation.
	</td>
	<td>
		<img src="examples/lightning.jpg" width="400">
		<b>Lightning</b>
		<p>Similar to a Brownian tree but faster to generate.
	</td>
</tr>
</table>

## Notes
* All wallpapers are 1024x768. If you have a different resolution, you can either change your wallpaper style to Strech or rewrite the programs. Sorry.

## References && Acknowledgements
* The *clouds* and *islands* generators rely on the super-fast Perlin noise generator I found here: https://gist.github.com/nowl/828013
* The *landscape* generator is shamelessly stolen from here: https://tyrellrummage.github.io/landscape/
* The *marrowlike* generator follows the recursive algorithm described here: http://pcg.wikidot.com/forum/t-79282/multiplicative-cascades-ish