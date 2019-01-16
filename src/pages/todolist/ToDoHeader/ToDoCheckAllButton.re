let styles = [%raw {| require("./ToDoCheckAllButton.scss") |}]
let component = ReasonReact.statelessComponent("ToDoCheckAllButton")

let make = (~completeAll: unit => unit, _children) => {
    ...component,

    render: _self => {
        <button className=styles##button onClick={_e => completeAll() }>
            <span className=styles##buttonText>{ ReasonReact.string({j|❯|j}) }</span>
        </button>
    }
}
