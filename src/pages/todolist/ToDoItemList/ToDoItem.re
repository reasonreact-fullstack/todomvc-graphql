let styles = [%raw {| require("./ToDoItem.scss") |}]
let component = ReasonReact.statelessComponent("ToDoItem")

let make = (~todo: ToDoTypes.todo, _children) => {
    ...component,

    render: _self => {
        <li className=styles##wrap>
            <button className=styles##checkbox></button>
            <span className=styles##text>{ ReasonReact.string(todo.content) }</span>
            <button className=styles##removeButton>{ ReasonReact.string({j|×|j}) }</button>
        </li>
    }
}
