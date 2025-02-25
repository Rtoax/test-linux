#!/usr/bin/env python3

import dbus

def list_dbus_names():
    # Connect to the system bus
    bus = dbus.SystemBus()

    # Get the object representing the bus
    obj = bus.get_object('org.freedesktop.DBus', '/org/freedesktop/DBus')

    # Get the interface for the object
    interface = dbus.Interface(obj, 'org.freedesktop.DBus')

    # List names
    names = interface.ListNames()

    # Print the names
    for name in names:
        print(name)

if __name__ == '__main__':
    list_dbus_names()
