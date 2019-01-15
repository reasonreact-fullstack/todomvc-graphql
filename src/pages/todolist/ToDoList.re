let component = ReasonReact.statelessComponent("ToDoList")

let make = (_children) => {
    ...component,

    render: _self => {
        <div>
            { ReasonReact.string("ToDoList") }
        </div>
    }
}
