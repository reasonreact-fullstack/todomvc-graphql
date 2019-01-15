let styles: ToDoListStyles.definition = [%raw {| require("./ToDoList.css") |}]

let component = ReasonReact.statelessComponent("ToDoList")

let make = (_children) => {
    ...component,

    render: _self => {
        <div className=styles##background>
            <h1 className=styles##title>{ ReasonReact.string("todos") }</h1>
            <Todos />
        </div>
    }
}
