socat TCP-LISTEN:1907,reuseaddr,fork exec:'./a.out',pty,stderr,setsid,sigint,sane


stty -icanon && socat - tcp:127.0.0.1:1907 && stty icanon
