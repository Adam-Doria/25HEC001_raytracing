# Dockerfile pour le développement du projet Rayborn (Alpine - version légère)
FROM alpine:3.18

# Installation des outils de développement C++
RUN apk add --no-cache \
    build-base \
    cmake \
    ninja \
    g++ \
    gdb \
    git \
    vim \
    nano \
    bash \
    clang-extra-tools \
    doxygen \
    graphviz

WORKDIR /app

# Attention j'copie pas le code source ici pour permettre le montage de volume lors du développement, du coup pensez bien à faire la commande docker run -it -v $(pwd):/app rayborn-dev

EXPOSE 5678

CMD ["/bin/bash"]
