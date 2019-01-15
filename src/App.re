let styles = [%raw {| require("./App.scss") |}]
type state = {
    page: Url.page,
};

type action = ChangePage(Url.page);

let component = ReasonReact.reducerComponent("App");

let make = (_children) => {
    ...component,
    initialState: () => {
        page: ToDoList,
    },

    didMount: self => {
        let watchID = ReasonReact.Router.watchUrl(url => {
            switch(url.path) {
            | [""] => self.send(ChangePage(ToDoList))
            | ["login"] => self.send(ChangePage(Login))
            | _ => self.send(ChangePage(Error404))
            }
        })
        self.onUnmount(() => ReasonReact.Router.unwatchUrl(watchID));
    },

    reducer: (action: action, _state: state) => {
        switch(action) {
        | ChangePage(page) => ReasonReact.Update({ page: page })
        }
    },

    render: self => {
        <>
        {switch(self.state.page) {
        | ToDoList => <ToDoList />
        | Login => <Login />
        | Error404 => <Error404 />
        }}
        </>
    }
}
