#!/bin/bash

curl -L https://oss.sonatype.org/content/groups/public/com/nativelibs4java/jnaerator/0.13-SNAPSHOT/jnaerator-0.13-20150328.111636-4-shaded.jar --output jnaerator.jar
java -jar jnaerator.jar /workspaces/LitLaunch/litlaunch-library-api/src/main/c/*.h -f -mode Directory