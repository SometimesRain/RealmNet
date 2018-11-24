![](/realmnet_logo.png)

RealmNet is a new, highly efficient proxy written in native C++. With a performance rivaling that of the hacked clients it was designed efficiency in mind. On top of having its plugins compiled to native code, its approach to reading packets differs from K Relay. Packets are not read at all if there is no plugin that needs them. This also means there is no need to write them to a new buffer for forwarding.

## Proxy in 2018?

With clients taking over the rotmg hacking scene, why make a new proxy?

Proxies still have their place as a tool of learning. I personally learned rotmg hacking with Realm Relay and K Relay. I hope to encourage new hackers getting started with rotmg hacking, and for them RealmNet is a good place to start. I wrote RealmNet to learn more C++ and learned to love the language I previously felt was so arcane and troublesome. It was also a good stepping stone to writing my own C++ bot.

I believe that by solving the performance issues and by making using the proxy seamless, it can challenge the clients. Proxies also have the added benefit of being easy to update.

## Getting started

Requirements:
* CMake 3.11 or higher
* Boost

Precompiled binaries for Boost on Visual Studio can be found [here](https://sourceforge.net/projects/boost/files/boost-binaries/). The MSVC version number has to match yours perfectly (14.1 for Visual Studio 2017). Only the 32-bit version will work with RealmNet.

----

1. Clone or download the repository.
2. Open **cmake-gui** and set the path to the source code to point to the RealmNet directory
3. Set your build path (if unsure, copy the row above and add "/build")
4. Press **Configure** and make sure your version of Visual Studio is selected. The generator name should **not** end in Win64.
5. After the configuration succeeds, press **Generate** and open the project with **Open Project**.
6. Change from **Debug** to **Release** and build the project.

If you get an error on step 4 and it says *Unable to find the requested Boost libraries* in red on the build log, you edit your environment variables:

1. Open your Control Panel and search for *environment*.
2. Select **Edit the system environment varibles** -> **Environment Variables...**
3. Create a new user variable **Boost_ROOT** and set the value to your boost installation folder path (e.g. `D:\boost\boost_1_67_0`)
4. Create **Boost_LIBRARYDIR** and set the value to your boost lib folder path (e.g. `D:\boost\boost_1_67_0\lib32-msvc-14.1`)
5. Restart **make-gui** and press **Configure** again

To get started with developing plugins, you should check out the [Plugin Documentation](https://github.com/SometimesRain/realmnet-plugin-doc).
