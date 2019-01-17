let styles = [%raw {| require("./ToDoItem.scss") |}]

type todoItem = ToDoTypes.todo;

type state = {
    editMode: bool,
};

type action = ChangeMode(bool);

let component = ReasonReact.reducerComponent("ToDoItem");

let make = (
    ~todo: todoItem, 
    ~toggleTodo: todoItem => unit,
    ~submit: todoItem => unit,
    _children
) => {
    ...component,
    initialState: () => {
        editMode: false,
    },

    reducer: (action: action, _state: state) => {
        switch(action) {
        | ChangeMode(mode) => ReasonReact.Update({ editMode: mode })
        }
    },

    render: self => {
        <li className=styles##wrap>
            <button 
                className=Cn.make([
                    styles##checkbox,
                    styles##completed->Cn.ifTrue(todo.completed),
                ])
                onClick={_e => toggleTodo(todo) }
            ></button>
            <span 
                className=Cn.make([
                    styles##text,
                    styles##completed->Cn.ifTrue(todo.completed),
                    styles##editText->Cn.ifTrue(self.state.editMode),
                ])
                onDoubleClick={ _e => self.send(ChangeMode(true)) }
                onKeyDown= { event => {
                    let keyCode = ReactEvent.Keyboard.keyCode(event);
                    switch(keyCode) {
                    | 13 => self.send(ChangeMode(false))
                    | 27 => self.send(ChangeMode(false))
                    | _ => ()
                    }
                }}
                onBlur= { _e => {
                    self.send(ChangeMode(false)) 
                }}
            >
                { switch(self.state.editMode) {
                | true => <ToDoInput submit text=todo.content />
                | false => ReasonReact.string(todo.content)
                }}
            </span>
            <button 
                className=Cn.make([
                    styles##removeButton,
                    styles##editText->Cn.ifTrue(self.state.editMode),
                ])
            >
                { ReasonReact.string({j|×|j}) }
            </button>
        </li>
    }
}
