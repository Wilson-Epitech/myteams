1. Introduction

MyTeams is a collaborative communication application protocol designed for managing teams, channels, threads, and personal messages. This document outlines the commands and their corresponding sequences required for interaction between the MyTeams server and client.

2. Mandatory Commands

The following commands are essential for communication between the MyTeams server and client:

    /login [“user_name”]: Authenticate the user with the provided username.
    /logout: Disconnect the client from the server.
    /users: Retrieve the list of all users on the domain.
    /user [“user_uuid”]: Fetch details about the specified user.
    /send [“user_uuid”] [“message_body”]: Send a message to a specific user.
    /messages [“user_uuid”]: List all messages exchanged with the specified user.
    /subscribe [“team_uuid”]: Subscribe to events of a team and its subdirectories.
    /subscribed ?[“team_uuid”]: List all subscribed teams or users subscribed to a team.
    /unsubscribe [“team_uuid”]: Unsubscribe from a team.
    /use ?[“team_uuid”] ?[“channel_uuid”] ?[“thread_uuid”]: Set the command context to a team/channel/thread.
    /create [“resource”]: Create a new team, channel, thread, or reply based on the context.
    /list: List all existing teams, channels, threads, or replies based on the context.
    /info: Display details of the current resource based on the context.

3. Command-Reply Sequences

The interactions between the client and server follow specific command-reply sequences:

    Connection Establishment:
        <- 000: Server ready for connection.

    /login $(username) -> Tries to connect with the username $(username).
        <- 001: User created.
        <- 002: User loaded.
        <- 003: User logged in.

    /logout -> Logout the client (and the user) from the server.
        <- 004: User disconnected.
        <- 005: Service closed.

    /user $(user_uuid) -> Gives information about a certain user.
        <- 008 $(uuid) $(name) $(connected)

    /users -> List all the users on the domain.
        <- 007 $(uuid) $(name) $(connected) , etc...
    
    /create $(name) $(description) -> Create a team if the context is at the root.
        <- 009 Event: Team $(uuid) $(name) about $(description) created.
        <- 039 Self: Team $(uuid) $(name) about $(description) created.
    
    /create $(name) $(description) -> Create a channel if the context is set to a team.
        <- 010 Channel $(uuid) $(name) about $(description) created.
    
    /create $(name) $(description) -> Create a team if their is no context.
        <- 009 Team $(uuid) $(name) about $(description) created.
    
    /create $(name) $(description) -> Create a team if their is no context.
        <- 009 Team $(uuid) $(name) about $(description) created.

4. Security

While password authentication is not required, security measures are implemented to restrict unauthorized access to certain functionalities based on user permissions.
