# Auth System
Auth System is a  ___java project___ that has an authentication system along with a database where to store users data.

### Used Libraries / Frameworks
* [H2 database](http://h2database.com/html/main.html) - database engine
* [JavaFX](https://openjfx.io/) - for GUI
* [Spring Security](https://spring.io/projects/spring-security) - BCrypt password hashing
* [Gson](https://github.com/google/gson) - json stuff

### Contribution
*will add a guide soon*

### Building (*currently broken*)

*maven build fails to get the dependency "com.sun.javafx"to include it in the classpath, making this JavaFX application throwing an error at execution due to missing javafx dependencies
 one way of overcoming this, is by using IntelliJ IDEA JavaFX artifact*

This project uses [maven](https://maven.apache.org/) as a dependency manager also as package builder

##### Requirments
* JDK 8 or newer
* Git (optional)

##### Compiling
1. `git clone https://github.com/openmindsclub/H4ckT0b3rF3st-2k20` or download this repository file in ZIP format then extract its content
2. browse to this directory:
```bash
cd /H4ckT0b3rF3st-2k20/projects/account-auth
```
3. run `mvn package`
4. wait for the process to finnish, the final jar file output is going to be in `/target` subfolder

## Misc
no Eclipse users allowed... jk you are all welcome !
