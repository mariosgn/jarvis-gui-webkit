# jarvis-gui-webkit
First view implementation of the [jarvis](http://mariosgn.github.io/jarvis-backend-node/) protocol.

# Quick install
This is a beta version, with also a beta installation process: just to have a look.

You will need qt-5.

```bash
    cd /tmp/
    git clone https://github.com/mariosgn/jarvis-gui-webkit.git
    git clone https://github.com/mariosgn/jarvis-backend-node/ 
    cd jarvis-gui-webkit/
    qmake
    make
    mkdir -p ~/.config/jarvis/views/
    vim  ~/.config/jarvis/views/simple_view.json
```

Now you should create a file like this one:

```bash
    {
    "width": 300,
    "height": 800,
    "x": 100,
    "y": 100,
    "forcedesktop": true,
    "themefile":"/tmp/jarvis/jarvis-backend-node/harmattan-like-demo/index.html",
}
```
and now run the view:

```bash
    ./jarvis-gui-webkit --view simple_view
}
```
# Docs
Still in beta [here](http://mariosgn.github.io/jarvis-backend-node/)
