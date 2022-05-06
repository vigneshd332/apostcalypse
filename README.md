# aPOSTcalypse

A tool to send a chain of HTTP requests to a server(s).

### Build

<ul>
<li> Run <code>build.bat</code> to build the program (Windows) or <code>build.sh</code> (Linux)</li>
</ul>

### Troubleshooting

<ul>
<li>If the program does not build, make sure you have Cmake and Make installed.</li>
<li>If you encounter a "error loading shared libraries" error on Linux, its most like because of Poco libraries getting installed to a different location. To solve this, copy all the Poco libraries from <code>/usr/local/lib</code> to <code>/usr/lib</code> manually or by running <code>sudo cp /usr/local/lib/libPoco* /usr/lib</code></li>
</ul>
