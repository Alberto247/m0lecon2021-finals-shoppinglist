FROM ubuntu:18.04

RUN apt-get update && apt-get upgrade -y
RUN apt-get install -y socat
RUN apt-get install -y libssl-dev

RUN useradd -ms /bin/sh pwn

WORKDIR /home/pwn

COPY ./flag.txt ./
COPY ./shoppingList ./

RUN chown -R root:pwn /home/pwn && chmod 750 /home/pwn && chown root:pwn /home/pwn/flag.txt && chmod 440 /home/pwn/flag.txt && chmod 550 /home/pwn/shoppingList

EXPOSE 8273

CMD ["socat", "-T60", "TCP-LISTEN:8273,reuseaddr,fork,su=pwn", "EXEC:/home/pwn/shoppingList,pty,raw,stderr,echo=0"]