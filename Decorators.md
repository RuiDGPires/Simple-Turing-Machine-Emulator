# Description of what decorators are supposed to do

## Override
Re-defines and existing connection.
Throws and error if the connetion does not exist.

## Surpress
Used to silence existance errors when defining a connection
For example, if a connection under this decorator already exists and is trying to be re-defined without @Override, it does nothing and does not throw an error.

This can be used together with @Override to always define a connection, even if it already exists.
